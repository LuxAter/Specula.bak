#include "specula/specula.hpp"

#include <chrono>
#include <future>
#include <glm/glm.hpp>
#include <random>
#include <thread>
#include <tuple>

#include "specula/cli/progress_bar.hpp"
#include "specula/fs.hpp"
#include "specula/image/image.hpp"
#include "specula/thread.hpp"

static std::mt19937 rand_gen_;
static std::uniform_real_distribution<double> rand_dist_;

void specula::render(const std::vector<std::shared_ptr<Primative>> &objs,
                     const std::vector<std::shared_ptr<Material>> &mats,
                     const std::size_t &spp, const float &fov,
                     const std::size_t &img_width,
                     const std::size_t &img_height,
                     const std::string &output_path, std::size_t index,
                     bool sequence) {
  std::random_device rd;
  rand_gen_ = std::mt19937(rd());
  std::string output_file = output_path;
  if (sequence) {
    std::string directory =
        output_path.substr(0, output_path.find_last_of('.'));
    if (fs::exists(directory)) {
      fs::remove_all(directory);
    }
    fs::create_directory(directory);
    output_file = fmt::format(
        "%s/%lu%s", directory.c_str(), index,
        output_path
            .substr(output_path.find_last_of('.'),
                    output_path.length() - output_path.find_last_of('.'))
            .c_str());
  }

  std::vector<std::shared_ptr<Primative>> visible_objs;
  for (auto &it : objs) {
    if (it->material_ != nullptr) {
      visible_objs.push_back(it);
    }
  }

  std::size_t block_size = static_cast<std::size_t>(std::sqrt(
      img_width * img_height / (4 * std::thread::hardware_concurrency())));
  std::size_t hblocks = static_cast<std::size_t>(
      std::ceil(img_width / static_cast<double>(block_size)));
  std::size_t vblocks = static_cast<std::size_t>(
      std::ceil(img_height / static_cast<double>(block_size)));
  std::size_t blocks = hblocks * vblocks;

  terminal::ProgressBar progress(
      fmt::format("Rendering %s",
                  (sequence ? std::to_string(index) : output_file).c_str()),
      blocks);

  Image img({img_width, img_height});

  thread::Pool pool(std::thread::hardware_concurrency());

  std::array<std::size_t, 5> block_size_data = {
      {hblocks, vblocks, block_size, img_width, img_height}};

  std::vector<std::future<
      std::tuple<std::size_t, std::vector<std::vector<std::array<double, 3>>>>>>
      pool_results;
  for (std::size_t i = 0; i < blocks; ++i) {
    pool_results.push_back(
        pool.enqueue(render_block, i, block_size_data, visible_objs, spp, fov));
  }
  while (pool_results.size() != 0) {
    for (std::size_t i = 0; i < pool_results.size(); ++i) {
      if (pool_results[i].wait_for(std::chrono::milliseconds(10)) !=
          std::future_status::ready)
        continue;
      auto [id, block] = pool_results[i].get();
      progress();
      std::size_t x_offset = (id % hblocks) * block_size;
      std::size_t y_offset = (id / hblocks) * block_size;
      for (std::size_t x = 0; x < block.size(); ++x) {
        for (std::size_t y = 0; y < block[x].size(); ++y) {
          img(x + x_offset, y + y_offset) = block[x][y];
        }
      }
      pool_results.erase(pool_results.begin() + i);
    }
    pool_results.erase(
        std::remove_if(
            pool_results.begin(), pool_results.end(),
            [](const std::future<
                std::tuple<std::size_t,
                           std::vector<std::vector<std::array<double, 3>>>>>
                   &it) { return !it.valid(); }),
        pool_results.end());
  }
  img.write(output_file);
}

std::tuple<std::size_t, std::vector<std::vector<std::array<double, 3>>>>
specula::render_block(const std::size_t &i,
                      const std::array<std::size_t, 5> &block_size,
                      const std::vector<std::shared_ptr<Primative>> &objs,
                      const std::size_t &spp, const float &fov) {
  std::vector<std::vector<std::array<double, 3>>> block(
      std::min(((i % block_size[0]) + 1) * block_size[2], block_size[3]) -
          (i % block_size[0]) * block_size[2],
      std::vector<std::array<double, 3>>(
          std::min(((i / block_size[0]) + 1) * block_size[2], block_size[4]) -
              (i / block_size[0]) * block_size[2],
          std::array<double, 3>{0.0, 0.0, 0.0}));
  float film_z =
      (block_size[3] / 2.0f) / static_cast<float>(std::tan(fov / 2.0));
  std::size_t x_offset = (i % block_size[0]) * block_size[2];
  std::size_t y_offset = (i / block_size[0]) * block_size[2];
  // std::array<double, 3> c = {{rand() / (double)RAND_MAX,
  //                             rand() / (double)RAND_MAX,
  //                             rand() / (double)RAND_MAX}};
  for (std::size_t x = 0; x < block.size(); ++x) {
    for (std::size_t y = 0; y < block[x].size(); ++y) {
      for (std::size_t s = 0; s < spp; ++s) {
        glm::vec3 dir(
            x + x_offset - (block_size[3] / 2.0 + rand_dist_(rand_gen_)),
            y + y_offset - (block_size[4] / 2.0) + rand_dist_(rand_gen_),
            film_z);
        auto [c, near_t] = ray_march(glm::vec3(0.0, 0.0, 0.0),
                                     glm::normalize(dir), objs, 1e-5f, 1e5f);
        block[x][y][0] += c.x / static_cast<double>(spp);
        block[x][y][1] += c.y / static_cast<double>(spp);
        block[x][y][2] += c.z / static_cast<double>(spp);
      }
    }
  }
  return std::make_tuple(i, block);
}

std::tuple<glm::vec3, float>
specula::ray_march(const glm::vec3 &origin, const glm::vec3 &direction,
                   const std::vector<std::shared_ptr<Primative>> &objs,
                   const float &epslion, const float &t_max,
                   std::size_t depth) {

  float rr_factor = 1.0f;
  if (depth >= 5) {
    const float rr_stop_prob = 0.1f;
    if (rand_dist_(rand_gen_) < rr_stop_prob) {
      return std::make_tuple(glm::vec3(0.0, 0.0, 0.0), 0.0f);
    }
    rr_factor = 1.0f / (1.0f - rr_stop_prob);
  }
  auto [t, obj, near_t] =
      ray_intersect(origin, direction, objs, epslion, t_max);
  if (obj == nullptr)
    return std::make_tuple(glm::vec3(0.0, 0.0, 0.0), near_t);
  glm::vec3 hp = origin + direction * t;
  glm::vec3 normal = obj->normal(hp, epslion);

  glm::vec3 clr(0.0, 0.0, 0.0);
  clr += obj->material_->base_color * obj->material_->emission * rr_factor;

  // Recursive ray march??? Doing both BRDF and BTDF?

  return std::make_tuple(clr, near_t);
}

std::tuple<float, std::shared_ptr<specula::Primative>, float>
specula::ray_intersect(const glm::vec3 &origin, const glm::vec3 &direction,
                       const std::vector<std::shared_ptr<Primative>> &objs,
                       const float &epslion, const float &t_max) {
  float t = 0.0f, near_t = 0.0f;
  std::shared_ptr<Primative> hit_obj = nullptr;
  while (t < t_max) {
    glm::vec3 p = origin + direction * t;
    float dt = std::numeric_limits<float>::infinity();
    for (auto &obj : objs) {
      float odt = obj->distance(p);
      if (odt < dt) {
        dt = odt;
        if (odt < epslion)
          hit_obj = obj;
      }
    }
    if (dt < epslion)
      break;
    else
      t += dt;
  }
  return std::make_tuple(t, hit_obj, near_t);
}
