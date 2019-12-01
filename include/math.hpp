#ifndef SPECULA_MATH_HPP_
#define SPECULA_MATH_HPP_

#include <cmath>

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace specula {
struct ray {
  glm::vec4 o;
  glm::vec3 d;
};

inline glm::vec3 operator*(const glm::mat4 &lhs, const glm::vec3 &rhs) {
  return lhs * glm::vec4(rhs, 0.0f);
}
inline glm::vec4 operator+(const glm::vec4 &lhs, const glm::vec3 &rhs) {
  return lhs + glm::vec4(rhs, 0.0f);
}
inline glm::vec4 operator-(const glm::vec4 &lhs, const glm::vec3 &rhs) {
  return lhs - glm::vec4(rhs, 0.0f);
}
} // namespace specula

#endif // SPECULA_MATH_HPP_
