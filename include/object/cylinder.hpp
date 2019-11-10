#ifndef SPECULA_OBJECT_CYLINDER_HPP_
#define SPECULA_OBJECT_CYLINDER_HPP_

#define GLM_FORCE_SWIZZLE

#include <glm/glm.hpp>

#include "object_class.hpp"

namespace specula {
namespace object {
class Cylinder : public Object {
public:
  Cylinder(const float &height, const float &radius)
      : Object([this](const glm::vec3 &p) {
          const glm::vec2 d = glm::abs(glm::vec2(glm::length(p.xz()), p.y)) -
                              glm::vec2(this->radius, this->height);
          return glm::min(glm::max(d.x, d.y), 0.0f) +
                 glm::length(glm::max(d, 0.0f));
        }),
        height(height), radius(radius) {}
  ~Cylinder() {}

  void set_height(const float &h) { height = h; }
  float get_height() const { return height; }
  void set_radius(const float &r) { radius = r; }
  float get_radius() const { return radius; }

  float height, radius;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_CYLINDER_HPP_
