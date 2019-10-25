#ifndef SPECULA_GEOMETRY_RAY_HPP_
#define SPECULA_GEOMETRY_RAY_HPP_

#include <limits>

#include <glm/glm.hpp>

#include "../material/material.hpp"

namespace specula {
class ray {
public:
  ray();
  ray(const glm::vec3 &origin, const glm::vec3 &direction,
      const std::shared_ptr<Material> &mat = nullptr);

  inline glm::vec3 operator()(const float &t) const { return o + d * t; }

  inline ray &operator*(const glm::mat4 &tran) {
    o = glm::vec3(tran * glm::vec4(o, 1.0));
    d = glm::vec3(tran * glm::vec4(d, 0.0));
    return *this;
  }
  inline ray operator*(const glm::mat4 &tran) const {
    return ray(glm::vec3(tran * glm::vec4(o, 1.0)),
               glm::vec3(tran * glm::vec4(d, 0.0)));
  }

  glm::vec3 o, d;
  std::shared_ptr<Material> medium;
};
} // namespace specula

#endif // SPECULA_GEOMETRY_RAY_HPP_
