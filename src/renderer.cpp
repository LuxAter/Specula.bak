#include "renderer.hpp"

#include <chrono>
#include <cmath>
#include <memory>
#include <thread>
#include <vector>

#include "filesystem.hpp"
#include "image/image.hpp"
#include "log.hpp"
#include "math/math.hpp"
#include "object/object.hpp"
#include "rand.hpp"
#include "thread.hpp"
#include "cli/progress_bar.hpp"

bool specula::renderer::render_frame(
    const fs::path &file,
    const std::vector<std::shared_ptr<object::Object>> &objs,
    const std::size_t &spp, const double &fov, const vec2<std::size_t> &res) {

  // std::size_t tile_size = static_cast<std::size_t>(
  //     std::sqrt(res.x * res.y / (32 * std::thread::hardware_concurrency())));
  std::size_t tile_size = 256 / std::thread::hardware_concurrency();
  std::size_t htiles = static_cast<std::size_t>(
      std::ceil(res.x / static_cast<double>(tile_size)));
  std::size_t vtiles = static_cast<std::size_t>(
      std::ceil(res.y / static_cast<double>(tile_size)));
  std::size_t tiles = htiles * vtiles;

  LINFO("Rendering {} Tiles", tiles);

  thread::Pool pool(std::thread::hardware_concurrency());
  std::vector<
      std::future<std::tuple<std::size_t, std::vector<std::vector<float3>>>>>
      pool_results;
  for (std::size_t tile_id = 0; tile_id < tiles; ++tile_id) {
    pool_results.push_back(pool.enqueue(
        render_tile, tile_id,
        vec4<std::size_t>{
            (tile_id % htiles) * tile_size, (tile_id / htiles) * tile_size,
            std::min(((tile_id / htiles) + 1) * tile_size, res.h) -
                (tile_id / htiles) * tile_size,
            std::min(((tile_id % htiles) + 1) * tile_size, res.w) -
                (tile_id % htiles) * tile_size},
        objs, spp, fov));
  }

  specula::image::Image img(res);

  cli::ProgressBar progress(fmt::format("Rendering {}", file.string()),
                                 tiles);

  while (pool_results.size() != 0) {
    for (std::size_t i = 0; i < pool_results.size(); ++i) {
      if (pool_results[i].wait_for(std::chrono::milliseconds(10)) !=
          std::future_status::ready)
        continue;
      auto [tile_id, tile] = pool_results[i].get();
      progress();
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
                std::tuple<std::size_t, std::vector<std::vector<float3>>>>
                   &it) { return !it.valid(); }),
        pool_results.end());
  }
  return img.write(file);
}

std::tuple<std::size_t, std::vector<std::vector<specula::float3>>>
specula::renderer::render_tile(
    const std::size_t &tile_id, const vec4<std::size_t> &tile,
    const std::vector<std::shared_ptr<object::Object>> &objs,
    const std::size_t &spp, const double &fov) {
  float3 color(rand::frand(), rand::frand(), rand::frand());
  std::vector<std::vector<float3>> tile_data(
      tile.w, std::vector<float3>(tile.h, color));
  return std::make_tuple(tile_id, tile_data);
}
