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
#include "thread.hpp"

#define T_MAX 1e5f
#define EPSILON 1e-5f

bool specula::renderer::render_frame(
    const fs::path &file,
    const std::vector<std::shared_ptr<object::Object>> &objs,
    const std::size_t &spp, const float &fov, const glm::uvec2 &res,
    const std::array<glm::vec3, 3> &camera) {

  std::size_t tile_size = static_cast<std::size_t>(
      std::sqrt(res.x * res.y / (32 * std::thread::hardware_concurrency())));
  // std::size_t tile_size = 256 / std::thread::hardware_concurrency();
  std::size_t htiles = static_cast<std::size_t>(
      std::ceil(res.x / static_cast<double>(tile_size)));
  std::size_t vtiles = static_cast<std::size_t>(
      std::ceil(res.y / static_cast<double>(tile_size)));
  std::size_t tiles = htiles * vtiles;

  LINFO("OBJS: {}", objs.size());
  LTRACE("EYE: {},{},{}", camera[0].x, camera[0].y, camera[0].z);
  LTRACE("CENTER: {},{},{}", camera[1].x, camera[1].y, camera[1].z);
  LTRACE("UP: {},{},{}", camera[2].x, camera[2].y, camera[2].z);


  float filmz = res.x / 2.0f / static_cast<float>(std::tan(fov / 2.0));
  glm::mat4 view = glm::inverse(glm::lookAt(camera[0], camera[1], camera[2]));

  LDEBUG("VIEW: {} {} {} {}", view[0][0], view[1][0], view[2][0], view[3][0]);
  LDEBUG("VIEW: {} {} {} {}", view[0][1], view[1][1], view[2][1], view[3][1]);
  LDEBUG("VIEW: {} {} {} {}", view[0][2], view[1][2], view[2][2], view[3][2]);
  LDEBUG("VIEW: {} {} {} {}", view[0][3], view[1][3], view[2][3], view[3][3]);

  glm::vec3 o(0,0,0), d(0,0,1);
  o = view * glm::vec4(o, 1.0f);
  d = view * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
  LDEBUG("{},{},{}->{},{},{}", o.x, o.y, o.z, d.x, d.y, d.z);
  d = view * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
  LDEBUG("{},{},{}->{},{},{}", o.x, o.y, o.z, d.x, d.y, d.z);
  d = view * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
  LDEBUG("{},{},{}->{},{},{}", o.x, o.y, o.z, d.x, d.y, d.z);

  thread::Pool pool(std::thread::hardware_concurrency());
  std::vector<
      std::future<std::tuple<std::size_t, std::vector<std::vector<glm::vec3>>>>>
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
        res, objs, spp, fov, filmz, view));
  }

  specula::image::Image img(res);

  // cli::ProgressBar progress(fmt::format("Rendering {}", file.string()),
  // tiles);

  while (pool_results.size() != 0) {
    for (std::size_t i = 0; i < pool_results.size(); ++i) {
      if (pool_results[i].wait_for(std::chrono::milliseconds(10)) !=
          std::future_status::ready)
        continue;
      auto [tile_id, tile] = pool_results[i].get();
      // progress();
      std::size_t x_offset = (tile_id % htiles) * tile_size;
      std::size_t y_offset = (tile_id / htiles) * tile_size;
      for (std::size_t x = 0; x < tile.size(); ++x) {
        for (std::size_t y = 0; y < tile[x].size(); ++y) {
          img(x + x_offset, y + y_offset, tile[x][y]);
        }
      }
      pool_results.erase(pool_results.begin() + i);
    }
    pool_results.erase(
        std::remove_if(
            pool_results.begin(), pool_results.end(),
            [](const std::future<
                std::tuple<std::size_t, std::vector<std::vector<glm::vec3>>>>
                   &it) { return !it.valid(); }),
        pool_results.end());
  }
  return img.write(file);
}

std::tuple<std::size_t, std::vector<std::vector<glm::vec3>>>
specula::renderer::render_tile(
    const std::size_t &tile_id, const glm::uvec4 &tile, const glm::uvec2 &res,
    const std::vector<std::shared_ptr<object::Object>> &objs,
    const std::size_t &spp, const float &fov, const float &filmz,
    const glm::mat4 &view) {
  std::vector<std::vector<glm::vec3>> tile_data(
      tile.z, std::vector<glm::vec3>(tile.w, {0.0, 0.0, 0.0}));
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
        glm::vec3 c =
            ray_march(o, glm::normalize(glm::vec3(view * glm::vec4(dir, 0.0f))),
                      objs, EPSILON, T_MAX, 0);
        tile_data[x][y] += c / static_cast<float>(spp);
      }
    }
  }
  return std::make_tuple(tile_id, tile_data);
}

glm::vec3 specula::renderer::ray_march(
    const glm::vec3 &o, const glm::vec3 &d,
    const std::vector<std::shared_ptr<object::Object>> &objs, const float &ep,
    const float &t_max, const std::size_t &depth) {
  float rr_factor = 1.0f;
  if (depth >= 5) {
    const float rr_stop_prob = 0.1f * depth;
    if (rand::frand() < rr_stop_prob)
      return glm::vec3(0.0f, 0.0f, 0.0f);
    rr_factor = 1.0f / (1.0f - rr_stop_prob);
  }
  auto [t, obj] = ray_intersect(o, d, objs, ep, t_max);
  if (obj == nullptr)
    return glm::vec3(0.0f, 0.0f, 0.0f);

  return rr_factor * glm::vec3{1.0, 1.0, 1.0};
}

std::tuple<float, std::shared_ptr<specula::object::Object>>
specula::renderer::ray_intersect(
    const glm::vec3 &o, const glm::vec3 &d,
    const std::vector<std::shared_ptr<object::Object>> &objs, const float &ep,
    const float &t_max) {
  float t = 0.0f;
  std::shared_ptr<object::Object> hit_obj = nullptr;
  while (t < t_max) {
    glm::vec3 p = o + t * d;
    float dt = std::numeric_limits<float>::infinity();
    for (auto &obj : objs) {
      float odt = obj->distance(p);
      if (odt < dt) {
        dt = odt;
        if (odt < ep)
          hit_obj = obj;
      }
    }
    if (dt < ep)
      break;
    else
      t += dt;
  }
  return std::make_tuple(t, hit_obj);
}
