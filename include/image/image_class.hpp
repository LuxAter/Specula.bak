#ifndef SPECULA_IMAGE_CLASS_HPP_
#define SPECULA_IMAGE_CLASS_HPP_

#include <array>
#include <cstdint>
#include <cstdlib>
#include <string_view>
#include <vector>

#include "../filesystem.hpp"
#include "../math.hpp"

namespace specula {
namespace image {
class Image {
public:
  Image(const std::size_t &pix_width, const std::size_t &pix_height);
  Image(const glm::uvec2 &resolution);
  bool write(const std::string_view &file);
  bool write(const fs::path &file);
  void normalize();
  void abs();

  inline void operator()(const std::size_t &x, const std::size_t &y,
                         const glm::vec3 &c) {
    std::size_t idx = resolution_.y * y + x;
    buffer_[idx + 0] = c.r;
    buffer_[idx + 1] = c.g;
    buffer_[idx + 2] = c.b;
  }

private:
  glm::uvec2 resolution_;
  std::vector<float> buffer_;
};
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_CLASS_HPP_
