#ifndef SPECULA_MATH_HPP_
#define SPECULA_MATH_HPP_

#include <cmath>
#include <memory>

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader/material.hpp"

namespace specula {
struct ray {
  glm::vec3 o;
  glm::vec3 d;
  std::shared_ptr<Material> medium;
};
std::tuple<glm::vec3, glm::vec3> inline make_ortho_coord_sys(
    const glm::vec3 &v1) {
  glm::vec3 v2, v3;
  if (glm::abs(v1.x) > glm::abs(v1.y))
    v2 = glm::vec3(-v1.z, 0.0f, v1.x) *
         (1.0f / glm::sqrt(v1.x * v1.x + v1.z * v1.z));
  else
    v2 = glm::vec3(0.0f, v1.z, -v1.y) *
         (1.0f / glm::sqrt(v1.y * v1.y + v1.z * v1.z));
  v3 = glm::cross(v1, v2);
  return std::make_tuple(v2, v3);
}

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
