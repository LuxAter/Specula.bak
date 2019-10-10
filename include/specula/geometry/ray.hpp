#ifndef SPECULA_GEOMETRY_RAY_HPP_
#define SPECULA_GEOMETRY_RAY_HPP_

#include <limits>

#include <glm/glm.hpp>

namespace specula {
class ray {
public:
  ray();
  ray(const glm::vec3 &origin, const glm::vec3 &direction,
      float t_max = std::numeric_limits<float>::infinity());

  inline glm::vec3 operator()(const float &t) const { return o + d * t; }

  inline ray &operator*(const glm::mat4 &tran) {
    o = glm::vec3(tran * glm::vec4(o, 1.0));
    d = glm::vec3(tran * glm::vec4(d, 0.0));
    return *this;
  }
  inline ray operator*(const glm::mat4 &tran) const {
    return ray(glm::vec3(tran * glm::vec4(o, 1.0)),
               glm::vec3(tran * glm::vec4(d, 0.0)), t_max);
  }

  glm::vec3 o, d;
  mutable float t_max;
};
} // namespace specula

#endif // SPECULA_GEOMETRY_RAY_HPP_
