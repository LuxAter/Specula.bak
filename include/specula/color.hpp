#ifndef SPECULA_COLOR_HPP_
#define SPECULA_COLOR_HPP_

#include <cstdint>
#include <vector>

#include <glm/glm.hpp>

namespace specula {
inline std::uint32_t rgb_int(const glm::vec3 &rgb) {
  return (static_cast<std::uint32_t>(rgb.r * 255) << 16) |
         (static_cast<std::uint32_t>(rgb.g * 255) << 8) |
         (static_cast<std::uint32_t>(rgb.b * 255) << 0);
}
inline glm::vec3 hsv_rgb(const glm::vec3 &hsv) {
  const float c = hsv.z * hsv.y;
  const float x = c * (1 - std::fabs(std::fmod(hsv.x / 60.0f, 2.0f) - 1.0f));
  const float m = hsv.z - c;
  if (hsv.x < 60.0f) {
    return {c + m, x + m, m};
  } else if (hsv.x < 120.0f) {
    return {x + m, c + m, m};
  } else if (hsv.x < 180.0f) {
    return {m, c + m, x + m};
  } else if (hsv.x < 240.0f) {
    return {m, x + m, c + m};
  } else if (hsv.x < 300.0f) {
    return {x + m, m, c + m};
  } else {
    return {c + m, m, x + m};
  }
}
void seed_rand_color(const glm::vec3 &seed);
glm::vec3 rand_color();
} // namespace specula

#endif // SPECULA_COLOR_HPP_
