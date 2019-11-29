#ifndef SPECULA_RAY_HPP_
#define SPECULA_RAY_HPP_

#include <glm/glm.hpp>

namespace specula {
struct ray {
  glm::vec4 o;
  glm::vec3 d;
};

glm::vec3 operator*(const glm::mat4 &lhs, const glm::vec3 &rhs) {
  return lhs * glm::vec4(rhs, 0.0f);
}
glm::vec4 operator+(const glm::vec4 &lhs, const glm::vec3 &rhs) {
  return lhs + glm::vec4(rhs, 0.0f);
}
glm::vec4 operator-(const glm::vec4 &lhs, const glm::vec3 &rhs) {
  return lhs - glm::vec4(rhs, 0.0f);
}
} // namespace specula

#endif // SPECULA_RAY_HPP_
