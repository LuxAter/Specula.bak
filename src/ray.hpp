#ifndef SPECULA_RAY_HPP_
#define SPECULA_RAY_HPP_

#include <glm/glm.hpp>

namespace specula {
struct ray {
  glm::vec3 o, d;
};

inline ray operator*(const glm::mat4& mat, const ray& r) {
  return {mat * glm::vec4(r.o, 1.0f), mat * glm::vec4(r.d, 0.0f)};
}

} // namespace specula

#endif // SPECULA_RAY_HPP_
