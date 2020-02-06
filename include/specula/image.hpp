#ifndef SPECULA_IMAGE_HPP_
#define SPECULA_IMAGE_HPP_

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace specula {
class Image {
public:
  Image(const uint32_t& w, const uint32_t& h, const float& default_r = 0.0f,
        const float& default_g = 0.0f, const float& default_b = 0.0f);
  Image(const glm::uvec2& dimensions,
        const glm::vec3& default_pixel = glm::vec3(0.0f, 0.0f, 0.0f));

  inline glm::vec3& at(const uint32_t& x, const uint32_t& y) {
    return pixels.at(y * width + x);
  }
  inline const glm::vec3& at(const uint32_t& x, const uint32_t& y) const {
    return pixels.at(y * width + x);
  }

  inline float* get_ptr() { return (float*)pixels.data(); }
  inline std::size_t size() const { return width * height * 3; }
  inline glm::uvec2 dim() const { return glm::uvec2(width, height); }

  uint32_t width, height;
  std::vector<glm::vec3> pixels;
};
} // namespace specula

#endif // SPECULA_IMAGE_HPP_
