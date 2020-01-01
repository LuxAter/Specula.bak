#include "cpu_render.hpp"

#include <chrono>
#include <future>
#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "specula/image.hpp"
#include "specula/log.hpp"
#include "specula/object.hpp"
#include "specula/rand.hpp"
#include "specula/ray.hpp"
#include "specula/thread.hpp"

#include "specula/shader/bsdf.hpp"

static glm::mat4 view_matrix;
static unsigned long spp, bounces;
static float film_z, t_max, ep;
static glm::vec3 sky;
static std::vector<std::shared_ptr<specula::Object>> objs;

std::array<unsigned long, 4> split_time(const double &total) {
  std::array<unsigned long, 4> res;
  res[0] = static_cast<unsigned long>(total) / 3600000;
  res[1] = (static_cast<unsigned long>(total) % 3600000) / 60000;
  res[2] = (static_cast<unsigned long>(total) % 60000) / 1000;
  res[3] = (static_cast<unsigned long>(total) % 1000);
  return res;
}

bool specula::cpu::render(const std::shared_ptr<Image> &img, const Scene &scene,
                          const RenderArgs &args) {
  view_matrix = glm::inverse(glm::lookAt(
      scene.get_camera_pos(), scene.get_camera_focus(), scene.get_camera_up()));
  spp = args.spp;
  bounces = args.bounces;
  film_z = args.res_width / (2.0f * std::tan(scene.get_camera_fov() / 2.0f));
  t_max = args.time_max;
  ep = args.epsilon;
  sky = scene.get_sky_color();
  objs = scene.get_visible();

  unsigned long htiles = static_cast<unsigned long>(
      std::ceil(args.res_width / static_cast<double>(args.tile_size)));
  unsigned long vtiles = static_cast<unsigned long>(
      std::ceil(args.res_height / static_cast<double>(args.tile_size)));
  unsigned long tiles = htiles * vtiles;

  std::function<glm::vec2(const glm::uvec2 &)> pixel_to_camera =
      [args](const glm::uvec2 &pos) -> glm::vec2 {
    return glm::vec2(pos.x - args.res_width / 2.0f + frand(),
                     pos.y - args.res_height / 2.0f + frand());
  };

  ThreadPool pool(args.threads);
  std::vector<std::future<unsigned long>> pool_results;
  for (unsigned long tile_id = 0; tile_id < tiles; ++tile_id) {
    pool_results.push_back(pool.enqueue(
        cpu::render_tile, tile_id,
        glm::uvec4{(tile_id % htiles) * args.tile_size,
                   (tile_id / htiles) * args.tile_size,
                   ((tile_id % htiles) * args.tile_size) +
                       std::min(static_cast<unsigned long>(
                                    ((tile_id % htiles) + 1) * args.tile_size),
                                args.res_width) -
                       (tile_id % htiles) * args.tile_size,
                   ((tile_id / htiles) * args.tile_size) +
                       std::min(static_cast<unsigned long>(
                                    ((tile_id / htiles) + 1) * args.tile_size),
                                args.res_height) -
                       (tile_id / htiles) * args.tile_size},
        img, pixel_to_camera));
  }

  unsigned long processed = 0;
  const unsigned long tile_count_len = std::to_string(tiles).size();
  double total_time = 0.0f;
  auto start = std::chrono::high_resolution_clock::now();
  while (pool_results.size() != 0) {
    for (unsigned long i = 0; i < pool_results.size(); ++i) {
      if (pool_results[i].wait_for(std::chrono::milliseconds(10)) !=
          std::future_status::ready)
        continue;
      unsigned long id = pool_results[i].get();
      processed++;
      double delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(
                              std::chrono::high_resolution_clock::now() - start)
                              .count() /
                          1e6;
      total_time += delta_time;
      double remaining_time = (total_time / processed) * (tiles - processed);
      auto [hour_total, min_total, sec_total, milli_total] =
          split_time(total_time);
      auto [hour_rem, min_rem, sec_rem, milli_rem] = split_time(remaining_time);
      LINFO("Rendered Tile {:>{}} [{:{}}/{}] ({:7.3f}%) Elapsed: "
            "{:02}:{:02}:{:02}.{:03} Remaining: {:02}:{:02}:{:02}.{:03}",
            id, tile_count_len, processed, tile_count_len, tiles,
            100.0f * static_cast<float>(processed) / static_cast<float>(tiles),
            hour_total, min_total, sec_total, milli_total, hour_rem, min_rem,
            sec_rem, milli_rem);
      start = std::chrono::high_resolution_clock::now();
      pool_results.erase(pool_results.begin() + i);
    }
    pool_results.erase(std::remove_if(pool_results.begin(), pool_results.end(),
                                      [](const std::future<unsigned long> &it) {
                                        return !it.valid();
                                      }),
                       pool_results.end());
  }
  auto [hour_total, min_total, sec_total, milli_total] = split_time(total_time);
  LINFO("Total Elapsed Time: {:02}:{:02}:{:02}.{:03}", hour_total, min_total,
        sec_total, milli_total);
  return true;
}
unsigned long specula::cpu::render_tile(
    const unsigned long &tile_id, const glm::uvec4 &bounds,
    const std::shared_ptr<Image> &img,
    const std::function<glm::vec2(const glm::uvec2 &)> &pix_to_world) {
  const glm::vec3 c(0.1 * frand(), 0.1 * frand(), 0.1 * frand());
  const glm::vec3 o = view_matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  for (unsigned long x = bounds.x; x < bounds.z; ++x) {
    for (unsigned long y = bounds.y; y < bounds.w; ++y) {
      for (unsigned long s = 0; s < spp; ++s) {
        glm::vec3 d(pix_to_world({x, y}), -film_z);
        img->set(x, y,
                 c + cpu::ray_trace({o,
                                     glm::normalize(glm::vec3(
                                         view_matrix * glm::vec4(d, 0.0f))),
                                     nullptr}));
      }
    }
  }
  return tile_id;
}

glm::vec3 specula::cpu::ray_trace(const Ray &ray, unsigned long depth) {
  if (depth >= bounces && frand() < 0.1f) {
    return glm::vec3(0.0f);
  }
  auto [t, obj] = cpu::ray_march(ray);
  if (obj == nullptr) {
    return sky;
  }
  glm::vec3 p = ray.o + t * ray.d;
  glm::vec3 normal =
      (ray.medium != nullptr) ? -(obj->normal(p, ep)) : obj->normal(p, ep);
  Ray ray_out = shader::sample_bsdf(ray, obj->material, normal, ep);
  if (ray_out.d == glm::vec3(0.0f))
    return glm::vec3(0.0f);
  return glm::clamp(shader::evaluate_bsdf(ray, ray_out, obj->material,
                                          cpu::ray_trace(ray_out, depth + 1),
                                          normal),
                    0.0f, 1.0f);
}

std::pair<float, std::shared_ptr<specula::Object>>
specula::cpu::ray_march(const Ray &ray) {
  float t = 0.0f;
  std::shared_ptr<Object> inter_obj = nullptr;
  bool first = true;
  while (t < t_max) {
    glm::vec3 p = ray.o + t * ray.d;
    float dt = std::numeric_limits<float>::infinity();
    for (auto &obj : objs) {
      float obj_dt = std::fabs(obj->sdf(p));
      if (obj_dt < dt) {
        dt = obj_dt;
        if (obj_dt < ep) {
          inter_obj = obj;
        }
      }
    }
    if (!first && dt < ep) {
      break;
    } else {
      t += dt;
    }
    first = false;
  }
  return std::make_pair(t, inter_obj);
}