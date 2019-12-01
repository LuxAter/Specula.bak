#include "renderer.hpp"

#include <chrono>
#include <cmath>
#include <memory>
#include <thread>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "cli/progress_bar.hpp"
#include "filesystem.hpp"
#include "image/image.hpp"
#include "log.hpp"
#include "object/object.hpp"
#include "rand.hpp"
#include "shader/shader.hpp"
#include "thread.hpp"

namespace specula::renderer {
std::vector<std::shared_ptr<object::Object>> objs;
glm::uvec2 res;
std::size_t min_bounce, spp;
float ep = std::numeric_limits<float>::epsilon() * 100.0f, t_max = 1e2f, filmz,
      fov;
glm::mat4 view;
} // namespace specula::renderer

bool specula::renderer::render_frame(
    const fs::path &file,
    const std::vector<std::shared_ptr<object::Object>> &in_objs,
    const std::array<bool, 3> &renders, const std::size_t &tile_size,
    const std::size_t &in_spp, const float &in_fov,
    const std::size_t &in_min_bounce, const glm::uvec2 &in_res,
    const std::array<glm::vec3, 3> &camera, const bool &denoise) {

  std::copy_if(in_objs.begin(), in_objs.end(), std::back_inserter(objs),
               [](const std::shared_ptr<object::Object> &o) {
                 return o->mat_ != nullptr;
               });
  if (objs.size() == 0) {
    LWARN("No object are visible, rendering empty frame");
  }
  res = in_res;
  min_bounce = in_min_bounce;
  spp = in_spp;
  fov = in_fov;

  std::size_t htiles = static_cast<std::size_t>(
      std::ceil(res.x / static_cast<double>(tile_size)));
  std::size_t vtiles = static_cast<std::size_t>(
      std::ceil(res.y / static_cast<double>(tile_size)));
  std::size_t tiles = htiles * vtiles;

  filmz = res.x / 2.0f / static_cast<float>(std::tan(fov / 2.0));
  view = glm::inverse(glm::lookAt(camera[0], camera[1], camera[2]));

  thread::Pool pool(std::thread::hardware_concurrency());
  std::vector<std::future<tile_response_t>> pool_results;
  for (std::size_t tile_id = 0; tile_id < tiles; ++tile_id) {
    pool_results.push_back(pool.enqueue(
        render_tile, tile_id,
        glm::uvec4{
            (tile_id % htiles) * tile_size,
            (tile_id / htiles) * tile_size,
            std::min(
                static_cast<unsigned int>(((tile_id % htiles) + 1) * tile_size),
                res.x) -
                (tile_id % htiles) * tile_size,
            std::min(
                static_cast<unsigned int>(((tile_id / htiles) + 1) * tile_size),
                res.y) -
                (tile_id / htiles) * tile_size,
        }));
  }

  specula::image::Image img(res);
  specula::image::Image albido(res);
  specula::image::Image normal(res);
  specula::image::Image depth(res);

  cli::ProgressBar progress(fmt::format("Rendering {}", file.string()), tiles);

  while (pool_results.size() != 0) {
    for (std::size_t i = 0; i < pool_results.size(); ++i) {
      if (pool_results[i].wait_for(std::chrono::milliseconds(10)) !=
          std::future_status::ready)
        continue;
      auto tile = pool_results[i].get();
      progress();
      std::size_t x_offset = (tile.id % htiles) * tile_size;
      std::size_t y_offset = (tile.id / htiles) * tile_size;
      for (std::size_t x = 0; x < tile.data.size(); ++x) {
        for (std::size_t y = 0; y < tile.data[x].size(); ++y) {
          img(x + x_offset, res.y - (1 + y + y_offset), tile.data[x][y]);
          albido(x + x_offset, res.y - (1 + y + y_offset), tile.albido[x][y]);
          normal(x + x_offset, res.y - (1 + y + y_offset), tile.normal[x][y]);
          depth(x + x_offset, res.y - (1 + y + y_offset),
                {tile.depth[x][y], tile.depth[x][y], tile.depth[x][y]});
        }
      }
      pool_results.erase(pool_results.begin() + i);
    }
    pool_results.erase(
        std::remove_if(
            pool_results.begin(), pool_results.end(),
            [](const std::future<tile_response_t> &it) { return !it.valid(); }),
        pool_results.end());
  }
  if (renders[0]) {
    albido.write(fs::path(file.parent_path().string() + file.stem().string() +
                          "-albido" + file.extension().string()));
  }
  if (renders[1]) {
    normal.abs();
    normal.write(fs::path(file.parent_path().string() + file.stem().string() +
                          "-normal" + file.extension().string()));
  }
  if (renders[2]) {
    depth.normalize();
    depth.write(fs::path(file.parent_path().string() + file.stem().string() +
                         "-depth" + file.extension().string()));
  }
  img.write(file);
  return true;
}

specula::renderer::tile_response_t
specula::renderer::render_tile(const std::size_t &tile_id,
                               const glm::uvec4 &tile) {
  std::vector<std::vector<glm::vec3>> tile_data(
      tile.z, std::vector<glm::vec3>(tile.w, {0.0, 0.0, 0.0}));
  std::vector<std::vector<glm::vec3>> tile_albido(
      tile.z, std::vector<glm::vec3>(tile.w, {0.0, 0.0, 0.0}));
  std::vector<std::vector<glm::vec3>> tile_normal(
      tile.z, std::vector<glm::vec3>(tile.w, {0.0, 0.0, 0.0}));
  std::vector<std::vector<float>> tile_depth(tile.z,
                                             std::vector<float>(tile.w, 0.0f));
  glm::vec4 o(0.0, 0.0, 0.0, 1.0f);
  o = view * o;
  for (std::size_t x = 0; x < tile.z; ++x) {
    for (std::size_t y = 0; y < tile.w; ++y) {
      for (std::size_t s = 0; s < spp; ++s) {
        glm::vec3 dir(static_cast<float>(x + tile.x) -
                          (static_cast<float>(res.x) / 2.0) + rand::frand(),
                      static_cast<float>(y + tile.y) -
                          (static_cast<float>(res.y) / 2.0) + rand::frand(),
                      -filmz);
        auto [c, a, n, d] =
            ray_march(specula::ray{o, glm::normalize(view * dir)}, 0);
        tile_data[x][y] += c / static_cast<float>(spp);
        tile_albido[x][y] += a / static_cast<float>(spp);
        tile_normal[x][y] += glm::normalize(n) / static_cast<float>(spp);
        tile_depth[x][y] += d / static_cast<float>(spp);
      }
    }
  }
  return tile_response_t{tile_id, tile_data, tile_albido, tile_normal,
                         tile_depth};
}

std::tuple<glm::vec3, glm::vec3, glm::vec3, float>
specula::renderer::ray_march(ray r, const std::size_t &depth) {
  float rr_factor = 1.0f;
  if (depth >= min_bounce) {
    const float rr_stop_prob = 0.01f;
    if (rand::frand() < rr_stop_prob)
      return std::make_tuple(glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
    rr_factor = 1.0f / (1.0f - rr_stop_prob);
    // rr_factor = 1.0f;
  }
  auto [t, obj] = ray_intersect(r);
  if (obj == nullptr)
    return std::make_tuple(glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 0.0f, 0.0f), t);

  glm::vec4 p = r.o + t * r.d;
  glm::vec3 normal = obj->calculate_normal(p, ep);

  const float emission = obj->mat_->emission;
  glm::vec3 clr = obj->mat_->base_color * emission * rr_factor;

  ray out = shader::sample_bsdf(p, r, normal, obj->mat_, ep);
  glm::vec3 incoming = std::get<0>(ray_march(out, depth + 1));
  clr += shader::evaluate(p, r, out, normal, incoming, obj->mat_);

  return std::make_tuple(glm::clamp(clr, 0.0f, 1.0f), obj->mat_->base_color,
                         normal, t);
}

std::tuple<float, std::shared_ptr<specula::object::Object>>
specula::renderer::ray_intersect(const ray &r) {
  float t = 0.0f;
  std::shared_ptr<object::Object> hit_obj = nullptr;
  bool first = true;
  while (t < t_max) {
    glm::vec4 p = r.o + (t * r.d);
    float dt = std::numeric_limits<float>::infinity();
    for (auto &obj : objs) {
      float odt = obj->distance(p);
      if (std::fabs(odt) < std::fabs(dt)) {
        dt = odt;
        if (std::fabs(odt) < ep)
          hit_obj = obj;
      }
    }
    if (!first && std::fabs(dt) < ep) {
      break;
    } else
      t += std::fabs(dt);
    first = false;
  }
  return std::make_tuple(t, hit_obj);
}
