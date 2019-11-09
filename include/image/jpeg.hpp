#ifndef SPECULA_IMAGE_JPEG_HPP_
#define SPECULA_IMAGE_JPEG_HPP_

#include <array>
#include <cstdlib>
#include <string_view>
#include <vector>

#include "../math/vec2.hpp"
#include "../math/vec3.hpp"

namespace specula {
namespace image {
bool write_jpeg(const std::string_view &file,
                const vec2<std::size_t> &resolutin,
                const std::vector<vec3<double>> &buffer);
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_JPEG_HPP_
