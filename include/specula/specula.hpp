#ifndef SPECULA_HPP_
#define SPECULA_HPP_

#include <future>
#include <glm/glm.hpp>
#include <thread>
#include <tuple>

#include "fmt.hpp"
#include "fs.hpp"
#include "image/image.hpp"
#include "log.hpp"
#include "material/material.hpp"
#include "primatives/primatives.hpp"
#include "version.hpp"

#include "cli/progress_bar.hpp"

namespace specula {
inline void version(unsigned &major, unsigned &minor, unsigned &patch) {
  major = SPECULA_VERSION_MAJOR;
  minor = SPECULA_VERSION_MINOR;
  patch = SPECULA_VERSION_PATCH;
}

void render(const std::vector<std::shared_ptr<Primative>> &objs,
            const std::vector<std::shared_ptr<Material>> &mats,
            const std::size_t &spp, const std::size_t &img_width,
            const std::size_t &img_height, const std::string &output_path,
            std::size_t index = 0, bool sequence = true);

std::tuple<std::size_t, std::vector<std::vector<std::array<double, 3>>>>
render_block(const std::size_t &i, const std::array<std::size_t, 5> &block_size,
             const std::vector<std::shared_ptr<Primative>> &objs,
             const std::size_t &spp);

std::tuple<float, std::shared_ptr<Primative>, float>
ray_march(const glm::vec3 &origin, const glm::vec3 &direction,
          const std::vector<std::shared_ptr<Primative>> &objs,
          const float &epslion, const float &t_max);

} // namespace specula

#endif // SPECULA_HPP_
