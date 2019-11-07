#ifndef SPECULA_IMAGE_JPEG_HPP_
#define SPECULA_IMAGE_JPEG_HPP_

#include <cstdlib>
#include <string_view>
#include <vector>
#include <array>

#include "../math/vec2.hpp"

namespace specula {
namespace image {
bool write_jpeg(const std::string_view &file,
                const vec2<std::size_t> &resolutin,
                const std::vector<std::array<double, 3>> &buffer);
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_JPEG_HPP_
