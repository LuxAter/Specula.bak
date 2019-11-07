#ifndef SPECULA_IMAGE_CLASS_HPP_
#define SPECULA_IMAGE_CLASS_HPP_

#include <cstdint>
#include <cstdlib>
#include <string_view>
#include <vector>
#include <array>

#include "../math/vec2.hpp"

namespace specula {
namespace image {
class Image {
public:
  Image(const std::size_t &pix_width, const std::size_t &pix_height);
  Image(const vec2<std::size_t> &resolution);
  bool write(const std::string_view &file);

private:
  vec2<std::size_t> resolution_;
  std::vector<std::array<double, 3>> buffer_;
};
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_CLASS_HPP_
