#ifndef SPECULA_IMAGE_PNG_HPP_
#define SPECULA_IMAGE_PNG_HPP_

#include <array>
#include <cstdlib>
#include <string_view>
#include <vector>

#include "../math.hpp"

namespace specula {
namespace image {
bool write_png(const std::string_view &file, const glm::uvec2 &resolution,
               const std::vector<float> &buffer);
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_PNG_HPP_
