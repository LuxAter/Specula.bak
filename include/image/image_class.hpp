#ifndef SPECULA_IMAGE_CLASS_HPP_
#define SPECULA_IMAGE_CLASS_HPP_

#include <array>
#include <cstdint>
#include <cstdlib>
#include <string_view>
#include <vector>

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>

#include "../filesystem.hpp"

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

  inline glm::vec3 &operator()(const std::size_t &x, const std::size_t &y) {
    return buffer_[resolution_.y * y + x];
  }
  inline void operator()(const std::size_t &x, const std::size_t &y,
                         const glm::vec3 &c) {
    buffer_[resolution_.y * y + x] = c;
  }
  inline const glm::vec3 &operator()(const std::size_t &x,
                                     const std::size_t &y) const {
    return buffer_[resolution_.y * y + x];
  }

private:
  glm::uvec2 resolution_;
  std::vector<glm::vec3> buffer_;
};
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_CLASS_HPP_
