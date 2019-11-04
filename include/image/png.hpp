#ifndef SPECULA_IMAGE_PNG_HPP_
#define SPECULA_IMAGE_PNG_HPP_

#include <cstdlib>
#include <string_view>
#include <vector>
#include <array>

#include "../util/util.hpp"

namespace specula {
namespace image {
bool write_png(const std::string_view &file,
               const Size<std::size_t> &resolution,
               const std::vector<std::array<double, 3>> &buffer);
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_PNG_HPP_
