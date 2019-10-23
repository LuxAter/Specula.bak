#ifndef SPECULA_MATH_HPP_
#define SPECULA_MATH_HPP_

#include <cmath>
#include <optional>
#include <tuple>

#include <glm/glm.hpp>

namespace specula {
template <typename _T>
std::optional<std::tuple<_T, _T>> quadratic(const _T &a, const _T &b,
                                            const _T &c) {
  _T disc = (b * b) - (4 * a * c);
  if (disc < 0)
    return std::optional<std::tuple<_T, _T>>();
  else if (disc == 0)
    return std::optional<std::tuple<_T, _T>>(std::make_tuple(b / 2.0, b / 2.0));
  else
    return std::optional<std::tuple<_T, _T>>(std::make_tuple(
        -b + std::sqrt(disc) / (2.0 * a), -b - std::sqrt(disc) / (2.0 * a)));
}

inline glm::vec2 disk_to_square(const glm::vec2 &p) {
  float r = glm::length(p);
  float phi = std::atan2(p.y, p.x) >= -M_PI / 4.0f
                  ? std::atan2(p.y, p.x)
                  : std::atan2(p.y, p.x) + 2.0f * M_PI;
  if (phi < M_PI / 4.0f) {
    return glm::vec2(r, 4.0f / M_PI * r * phi);
  } else if (phi < 3.0f * M_PI / 4.0f) {
    return glm::vec2(-4.0f / M_PI * r * (phi - M_PI / 2.0), r);
  } else if (phi < 5.0f * M_PI / 4.0f) {
    return glm::vec2(-r, -4.0f / M_PI * r * (phi - M_PI));
  } else {
    return glm::vec2(4.0f / M_PI * r * (phi - 3.0f * M_PI / 2.0f), -r);
  }
}
inline glm::vec2 square_to_disk(const glm::vec2 &p) {
  if (p.x * p.x > p.y * p.y) {
    return glm::vec2(p.x, M_PI / 4.0f * p.y / p.x);
  } else if (p.x * p.x <= p.y * p.y && p.y != 0) {
    return glm::vec2(p.y, M_PI / 2.0f - M_PI / 4.0f * p.x / p.y);
  } else {
    return glm::vec2(0.0f, 0.0f);
  }
}

} // namespace specula

#endif // SPECULA_MATH_HPP_
