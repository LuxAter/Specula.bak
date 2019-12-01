#ifndef SPECULA_OBJECT_PLANE_HPP_
#define SPECULA_OBJECT_PLANE_HPP_

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>

#include "object_class.hpp"

namespace specula {
namespace object {
class Plane : public Object {
public:
  Plane(const float &x, const float &y, const float &z, const float &w)
      : Object(
            [this](const glm::vec3 &p) {
              return glm::dot(p, -this->normal.xyz()) - this->normal.w;
            },
            "return dot(p, {{ normal }}.xyz) - {{ normal.w }};",
            {{"normal", &this->normal}, {"normal.w", &this->normal.w}}),
        normal(x, y, z, w) {}
  ~Plane() {}
  glm::vec4 normal;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_PLANE_HPP_
