#ifndef SPECULA_OBJECT_PLANE_HPP_
#define SPECULA_OBJECT_PLANE_HPP_

#include <string>

#include "../math.hpp"
#include "object_class.hpp"

namespace specula::object {
class Plane : public ObjectBase, public std::enable_shared_from_this<Plane> {
public:
  Plane(const float &x, const float &y, const float &z, const float &w)
      : ObjectBase(
            [this](const glm::vec3 &p) {
              return glm::dot(p, this->normal.xyz()) + this->normal.w;
            },
            {{"normal", &(this->normal)}}),
        normal(x, y, z, w) {}
  Plane(const glm::vec4 &normal)
      : ObjectBase(
            [this](const glm::vec3 &p) {
              return glm::dot(p, this->normal.xyz()) + this->normal.w;
            },
            {{"normal", &(this->normal)}}),
        normal(normal) {}
  glm::vec4 normal;

  ObjectOperators(Plane)
};
} // namespace specula::object

#endif // SPECULA_OBJECT_PLANE_HPP_
