#include "cpu_renderer.hpp"

#include <chrono>
#include <limits>
#include <thread>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "specula/image.hpp"
#include "specula/log.hpp"
#include "specula/scene.hpp"
#include "specula/settings.hpp"

#include "ray.hpp"
#include "specula/rand.hpp"
#include "thread.hpp"

#include "specula/color.hpp"

static const specula::Settings *settings = nullptr;
static const specula::Scene *scene = nullptr;
static unsigned htiles, tiles;
static glm::mat4 view;
static float filmz;

specula::Image specula::cpu::render(const Settings *render_settings,
                                    const Scene *render_scene) {
  LINFO("Utilizing CPU Renderer");
  settings = render_settings;
  scene = render_scene;
  view = glm::inverse(glm::lookAt(scene->get_camera_pos(),
                                  scene->get_camera_focus(),
                                  scene->get_camera_up()));
  filmz = settings->get_width() / (2.0f * std::tan(scene->get_fov() / 2.0f));
  if (settings->get_tiling()) {
    htiles = static_cast<unsigned>(std::ceil(
        settings->get_width() / static_cast<float>(settings->get_size())));
    unsigned vtiles = static_cast<unsigned>(std::ceil(
        settings->get_height() / static_cast<float>(settings->get_size())));
    tiles = htiles * vtiles;
  } else {
    tiles = settings->get_size();
  }

  specula::Image img(settings->get_width(), settings->get_height());

  ThreadPool pool(settings->get_threads());
  std::vector<std::future<unsigned long>> pool_results;
  for (unsigned long tile_id = 0; tile_id < tiles; ++tile_id) {
    pool_results.push_back(pool.enqueue(cpu::render_tile, tile_id, &img));
  }

  unsigned long processed = 0;
  const unsigned pad_width = std::to_string(tiles).size();
  double total_time = 0.0f;
  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();
  while (pool_results.size() != 0) {
    for (std::size_t i = 0; i < pool_results.size(); ++i) {
      if (pool_results[i].wait_for(std::chrono::milliseconds(10)) !=
          std::future_status::ready)
        continue;
      unsigned long id = pool_results[i].get();
      pool_results.erase(pool_results.begin() + i);
      double delta_t = std::chrono::duration_cast<std::chrono::milliseconds>(
                           std::chrono::high_resolution_clock::now() - start)
                           .count() /
                       1000;
      total_time += delta_t;
      processed++;

      unsigned ehour = static_cast<unsigned>(total_time) / 3600;
      unsigned emin = (static_cast<unsigned>(total_time) % 3600) / 60;
      unsigned esec = (static_cast<unsigned>(total_time) % 60);
      unsigned emilli = (static_cast<unsigned>(total_time) * 1000) % 1000;
      double remaining = (total_time / processed) * (tiles - processed);
      unsigned rhour = static_cast<unsigned>(remaining) / 3600;
      unsigned rmin = (static_cast<unsigned>(remaining) % 3600) / 60;
      unsigned rsec = (static_cast<unsigned>(remaining) % 60);
      unsigned rmilli = (static_cast<unsigned>(remaining) * 1000) % 1000;

      LINFO("Rendered Tile {:>{}} [{:>{}}/{}] ({:7.3f}%) Elapsed: "
            "{:02}:{:02}:{:02}.{:03} Remaining: {:02}:{:02}:{:02}.{:03}",
            id, pad_width, processed, pad_width, tiles,
            100.0f * processed / tiles, ehour, emin, esec, emilli, rhour, rmin,
            rsec, rmilli);

      start = std::chrono::high_resolution_clock::now();
    }
    pool_results.erase(std::remove_if(pool_results.begin(), pool_results.end(),
                                      [](const std::future<unsigned long> &it) {
                                        return !it.valid();
                                      }),
                       pool_results.end());
  }
  return img;
}

unsigned long specula::cpu::render_tile(const unsigned long &tile_id,
                                        specula::Image *img) {
  glm::vec3 c = rand_color();
  glm::uvec2 start((tile_id % htiles) * settings->get_size(),
                   (tile_id / htiles) * settings->get_size());
  glm::uvec2 stop =
      glm::min(start + glm::uvec2(settings->get_size()),
               glm::uvec2(settings->get_width(), settings->get_height()));
  for (unsigned px = start.x; px < stop.x; ++px) {
    for (unsigned py = start.y; py < stop.y; ++py) {
      img->set(px, py, cpu::ray_march(cpu::camera_sample(px, py)));
    }
  }
  return tile_id;
}

glm::vec3 specula::cpu::ray_march(const ray &r, unsigned depth) {
  if(depth >= settings->get_bounces()) {
    if(frand() < settings->get_roulette_prob()) {
      return glm::vec3(0.0f);
    }
  }
  auto [t, obj] = cpu::ray_intersect(r);
  if(obj == nullptr) {
    return scene->get_sky();
  }
}

std::pair<float, std::shared_ptr<specula::Objct>> specual::cpu::ray_intersect(const ray& r) {
  float t = 0.0f;
  std::shared_ptr<Object> hit_obj = nullptr;
  while(t < settings->max_dist) {
    const glm::vec3 p = r.o + (t * r.d);
    float dt = std::numeric_limits<float>::infinity();
    for(auto& obj : scene->objects) {
      float obj_dt = std::fabs(obj->distance(p));
    }
  }
}

specula::ray specula::cpu::camera_sample(const unsigned &px,
                                         const unsigned &py) {
  switch (scene->get_projection()) {
  case PERSPECTIVE: {
    switch (settings->get_sampler()) {
    case NONE: {
      return ray{glm::vec3(0.0f),
                 glm::vec3(px - settings->get_width() / 2.0f,
                           py - settings->get_height() / 2.0f, -filmz)};
    }
    case JITTER: {
      return ray{glm::vec3(0.0f),
                 glm::vec3(px - settings->get_width() / 2.0f + frand(),
                           py - settings->get_height() / 2.0f + frand(),
                           -filmz)};
    }
    case SOBOL: {
      LWARNING("Sobol Method has not yet been implemented. See: {}",
               "https://en.wikipedia.org/wiki/Sobol_sequence");
      break;
    }
    case MULTI_JITTER: {
      LWARNING(
          "Multi Jitter Method has not yet been implemented. See: {}",
          "http://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf");
      break;
    }
    };
    break;
  }
  case ORTHOGRAPHIC: {
    switch (settings->get_sampler()) {
    case NONE: {
      const glm::vec2 camera_space(px - settings->get_width() / 2.0f,
                                   py - settings->get_height() / 2.0f);
      return ray{glm::vec3(camera_space, 0.0f),
                 glm::vec3(camera_space, -filmz)};
    }
    case JITTER: {
      const glm::vec2 camera_space(px - settings->get_width() / 2.0f + frand(),
                                   py - settings->get_height() / 2.0f +
                                       frand());
      return ray{glm::vec3(camera_space, 0.0f),
                 glm::vec3(camera_space, -filmz)};
    }
    case SOBOL: {
      LWARNING("Sobol Method has not yet been implemented. See: {}",
               "https://en.wikipedia.org/wiki/Sobol_sequence");
      break;
    }
    case MULTI_JITTER: {
      LWARNING(
          "Multi Jitter Method has not yet been implemented. See: {}",
          "http://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf");
      break;
    }
    };
    break;
  }
  };
}
