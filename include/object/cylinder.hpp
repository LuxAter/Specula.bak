#ifndef SPECULA_OBJECT_CYLINDER_HPP_
#define SPECULA_OBJECT_CYLINDER_HPP_

#include <string>

#include "../math.hpp"
#include "object_class.hpp"

namespace specula::object {
class Cylinder : public ObjectBase,
                 public std::enable_shared_from_this<Cylinder> {
public:
  Cylinder(const float &r, const float &h)
      : ObjectBase(
            [this](const glm::vec3 &p) {
              const glm::vec2 d = glm::abs(glm::vec2(glm::length(p.xz()), p.y)) -
                                  glm::vec2(this->height, this->radius);
              return std::min(std::max(d.x, d.y), 0.0f) +
                     glm::length(glm::max(d, 0.0f));
            },
            {{"radius", &(this->radius)}, {"height", &(this->height)}}),
        radius(r), height(h) {}
  float radius, height;

  ObjectOperators(Cylinder)
};
} // namespace specula::object

#endif // SPECULA_OBJECT_CYLINDER_HPP_
