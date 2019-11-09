#ifndef SPECULA_IMAGE_CLASS_HPP_
#define SPECULA_IMAGE_CLASS_HPP_

#include <array>
#include <cstdint>
#include <cstdlib>
#include <string_view>
#include <vector>

#include "../filesystem.hpp"
#include "../math/vec2.hpp"
#include "../math/vec3.hpp"

namespace specula {
namespace image {
class Image {
public:
  Image(const std::size_t &pix_width, const std::size_t &pix_height);
  Image(const vec2<std::size_t> &resolution);
  bool write(const std::string_view &file);
  bool write(const fs::path &file);

  inline vec3<double> &operator()(const std::size_t &x, const std::size_t &y) {
    return buffer_[resolution_.w * y + x];
  }
  inline void operator()(const std::size_t &x, const std::size_t &y,
                          const vec3<double> &c) {
    buffer_[resolution_.w * y + x] = c;
  }
  inline const vec3<double> &operator()(const std::size_t &x,
                                        const std::size_t &y) const {
    return buffer_[resolution_.w * y + x];
  }

private:
  vec2<std::size_t> resolution_;
  std::vector<vec3<double>> buffer_;
};
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_CLASS_HPP_
