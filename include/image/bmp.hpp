#ifndef SPECULA_IMAGE_BMP_HPP_
#define SPECULA_IMAGE_BMP_HPP_

#include <array>
#include <cstdlib>
#include <string_view>
#include <vector>

#include <glm/glm.hpp>

namespace specula {
namespace image {
bool write_bmp(const std::string_view &file, const glm::uvec2 &resolution,
               const std::vector<glm::vec3> &buffer);
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_PNG_HPP_
