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

/**
 * @brief Core rendering function
 *
 * This function takes the parameters that are defined by the user, and
 * produces and saves the output image.
 *
 * @param objs Vector of object pointers.
 * @param mats Vector of material pointers.
 * @param spp Samples per pixel to use. More produces a better image.
 * @param fov Field of View for the camera.
 * @param img_width Width of the ouput image in pixels.
 * @param img_height Height of the output image in pixels.
 * @param output_path Output path/directory.
 * @param index Image number in a sequence or 0.
 * @param sequence Boolean if the image is part of a sequence.
 */
void render(const std::vector<std::shared_ptr<Primative>> &objs,
            const std::vector<std::shared_ptr<Material>> &mats,
            const std::size_t &spp, const float &fov,
            const std::size_t &img_width, const std::size_t &img_height,
            const std::string &output_path, std::size_t index = 0,
            bool sequence = true);

std::tuple<std::size_t, std::vector<std::vector<std::array<double, 3>>>>
render_block(const std::size_t &i, const std::array<std::size_t, 5> &block_size,
             const std::vector<std::shared_ptr<Primative>> &objs,
             const std::size_t &spp, const float &fov);

std::tuple<glm::vec3, float>
ray_march(const glm::vec3 &origin, const glm::vec3 &direction,
          const std::vector<std::shared_ptr<Primative>> &objs,
          const float &epslion, const float &t_max, std::size_t depth = 0);

std::tuple<float, std::shared_ptr<Primative>, float>
ray_intersect(const glm::vec3 &origin, const glm::vec3 &direction,
              const std::vector<std::shared_ptr<Primative>> &objs,
              const float &epslion, const float &t_max);

} // namespace specula

#endif // SPECULA_HPP_
