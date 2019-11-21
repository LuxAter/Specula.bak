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

#define T_MAX 1e2f

static float EPSILON = std::numeric_limits<float>::epsilon() * 100.0f;

bool specula::renderer::render_frame(
    const fs::path &file,
    const std::vector<std::shared_ptr<object::Object>> &objs,
    const std::array<bool, 3> &renders, const std::size_t &tile_size,
    const std::size_t &spp, const float &fov, const std::size_t &min_bounce,
    const glm::uvec2 &res, const std::array<glm::vec3, 3> &camera,
    const bool &denoise) {

  std::vector<std::shared_ptr<object::Object>> reduced_objs;
  std::copy_if(objs.begin(), objs.end(), std::back_inserter(reduced_objs),
               [](const std::shared_ptr<object::Object> &o) {
                 return o->mat_ != nullptr;
               });
  if (reduced_objs.size() == 0) {
    LWARN("No object are visible, rendering empty frame");
  }

  std::size_t htiles = static_cast<std::size_t>(
      std::ceil(res.x / static_cast<double>(tile_size)));
  std::size_t vtiles = static_cast<std::size_t>(
      std::ceil(res.y / static_cast<double>(tile_size)));
  std::size_t tiles = htiles * vtiles;

  float filmz = res.x / 2.0f / static_cast<float>(std::tan(fov / 2.0));
  glm::mat4 view = glm::inverse(glm::lookAt(camera[0], camera[1], camera[2]));

  thread::Pool pool(std::thread::hardware_concurrency());
  std::vector<std::future<std::tuple<
      std::size_t, std::vector<std::vector<glm::vec3>>,
      std::vector<std::vector<glm::vec3>>, std::vector<std::vector<glm::vec3>>,
      std::vector<std::vector<float>>>>>
      pool_results;
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
        },
        res, reduced_objs, spp, fov, min_bounce, filmz, view));
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
      auto [tile_id, tile, tile_albido, tile_normal, tile_depth] =
          pool_results[i].get();
      progress();
      std::size_t x_offset = (tile_id % htiles) * tile_size;
      std::size_t y_offset = (tile_id / htiles) * tile_size;
      for (std::size_t x = 0; x < tile.size(); ++x) {
        for (std::size_t y = 0; y < tile[x].size(); ++y) {
          img(x + x_offset, res.y - (1 + y + y_offset), tile[x][y]);
          albido(x + x_offset, res.y - (1 + y + y_offset), tile_albido[x][y]);
          normal(x + x_offset, res.y - (1 + y + y_offset), tile_normal[x][y]);
          depth(x + x_offset, res.y - (1 + y + y_offset),
                {tile_depth[x][y], tile_depth[x][y], tile_depth[x][y]});
        }
      }
      pool_results.erase(pool_results.begin() + i);
    }
    pool_results.erase(
        std::remove_if(
            pool_results.begin(), pool_results.end(),
            [](const std::future<
                std::tuple<std::size_t, std::vector<std::vector<glm::vec3>>,
                           std::vector<std::vector<glm::vec3>>,
                           std::vector<std::vector<glm::vec3>>,
                           std::vector<std::vector<float>>>> &it) {
              return !it.valid();
            }),
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

std::tuple<std::size_t, std::vector<std::vector<glm::vec3>>,
           std::vector<std::vector<glm::vec3>>,
           std::vector<std::vector<glm::vec3>>, std::vector<std::vector<float>>>
specula::renderer::render_tile(
    const std::size_t &tile_id, const glm::uvec4 &tile, const glm::uvec2 &res,
    const std::vector<std::shared_ptr<object::Object>> &objs,
    const std::size_t &spp, const float &fov, const std::size_t &min_bounce,
    const float &filmz, const glm::mat4 &view) {
  std::vector<std::vector<glm::vec3>> tile_data(
      tile.z, std::vector<glm::vec3>(tile.w, {0.0, 0.0, 0.0}));
  std::vector<std::vector<glm::vec3>> tile_albido(
      tile.z, std::vector<glm::vec3>(tile.w, {0.0, 0.0, 0.0}));
  std::vector<std::vector<glm::vec3>> tile_normal(
      tile.z, std::vector<glm::vec3>(tile.w, {0.0, 0.0, 0.0}));
  std::vector<std::vector<float>> tile_depth(tile.z,
                                             std::vector<float>(tile.w, 0.0f));
  glm::vec3 o(0.0, 0.0, 0.0);
  o = view * glm::vec4(o, 1.0f);
  for (std::size_t x = 0; x < tile.z; ++x) {
    for (std::size_t y = 0; y < tile.w; ++y) {
      for (std::size_t s = 0; s < spp; ++s) {
        glm::vec3 dir(static_cast<float>(x + tile.x) -
                          (static_cast<float>(res.x) / 2.0) + rand::frand(),
                      static_cast<float>(y + tile.y) -
                          (static_cast<float>(res.y) / 2.0) + rand::frand(),
                      -filmz);
        auto [c, a, n, d] =
            ray_march(o, glm::normalize(glm::vec3(view * glm::vec4(dir, 0.0f))),
                      objs, EPSILON, T_MAX, 0, min_bounce);
        tile_data[x][y] += c / static_cast<float>(spp);
        tile_albido[x][y] += a / static_cast<float>(spp);
        tile_normal[x][y] += glm::normalize(n) / static_cast<float>(spp);
        tile_depth[x][y] += d / static_cast<float>(spp);
      }
    }
  }
  return std::make_tuple(tile_id, tile_data, tile_albido, tile_normal,
                         tile_depth);
}

std::tuple<glm::vec3, glm::vec3, glm::vec3, float> specula::renderer::ray_march(
    const glm::vec3 &o, const glm::vec3 &d,
    const std::vector<std::shared_ptr<object::Object>> &objs, const float &ep,
    const float &t_max, const std::size_t &depth,
    const std::size_t &min_bounce) {
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
  auto [t, obj] = ray_intersect(o, d, objs, ep, t_max);
  if (obj == nullptr)
    return std::make_tuple(glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 0.0f, 0.0f), t);

  glm::vec3 p = o + t * d;
  glm::vec3 normal = obj->calculate_normal(p, ep);

  const float emission = obj->mat_->emission;
  glm::vec3 clr = obj->mat_->base_color * emission * rr_factor;

  if (obj->mat_->type == material::Type::DIFFUSE) {
    auto [rotx, roty] = shader::make_ortho_coord_sys(normal);
    const float u1 = rand::frand();
    const float u2 = rand::frand();
    const double r = glm::sqrt(1.0 - u1 * u1);
    const double phi = 2.0f * M_PI * u2;
    glm::vec3 sampled_dir(glm::cos(phi) * r, glm::sin(phi) * r, u1);
    glm::vec3 dir;
    dir.x = glm::dot(glm::vec3(rotx.x, roty.x, normal.x), sampled_dir);
    dir.y = glm::dot(glm::vec3(rotx.y, roty.y, normal.y), sampled_dir);
    dir.z = glm::dot(glm::vec3(rotx.z, roty.z, normal.z), sampled_dir);
    float cost = glm::dot(dir, normal);
    clr += rr_factor * 2.0f *
           (std::get<0>(ray_march(p + (2.0f * ep * normal), dir, objs, ep,
                                  t_max, depth + 1, min_bounce)) *
            obj->mat_->base_color) *
           cost;
  } else if (obj->mat_->type == material::Type::SPECULAR) {
    glm::vec3 dir = glm::reflect(d, normal);
    clr +=
        rr_factor * std::get<0>(ray_march(p + (2.0f * ep * normal), dir, objs,
                                          ep, t_max, depth + 1, min_bounce));
  } else if (obj->mat_->type == material::Type::REFRACTIVE) {
    float n = obj->mat_->ior;
    float r0 = (1.0f - n) / (1.0f + n);
    r0 = r0 * r0;
    n = 1.0f / n;
    float cost1 = -glm::dot(normal, d);
    float cost2 = 1.0f - n * n * (1.0f - cost1 * cost1);
    float rprob = r0 + (1.0f - r0) * glm::pow(1.0f - cost1, 5.0f);
    glm::vec3 dir;
    if (cost2 > 0 && rand::frand() > rprob) {
      dir = glm::normalize((d * n) + (normal * (n * cost1 - glm::sqrt(cost2))));
    } else {
      dir = glm::normalize(d + normal * (cost1 * 2));
    }
    clr += std::get<0>(ray_march(p - (2.0f * ep * normal), dir, objs, ep, t_max,
                                 depth + 1, min_bounce)) *
           1.15f * rr_factor;
  }

  return std::make_tuple(glm::clamp(clr, 0.0f, 1.0f), obj->mat_->base_color,
                         normal, t);
}

std::tuple<float, std::shared_ptr<specula::object::Object>>
specula::renderer::ray_intersect(
    const glm::vec3 &o, const glm::vec3 &d,
    const std::vector<std::shared_ptr<object::Object>> &objs, const float &ep,
    const float &t_max) {
  float t = 0.0f;
  std::shared_ptr<object::Object> hit_obj = nullptr;
  bool first = true;
  while (t < t_max) {
    glm::vec3 p = o + (t * d);
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
