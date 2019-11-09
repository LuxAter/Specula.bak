#ifndef SPECULA_OBJECT_SPHERE_HPP_
#define SPECULA_OBJECT_SPHERE_HPP_

#include "../math/math.hpp"
#include "object_class.hpp"

namespace specula {
namespace object {
class Sphere : public Object {
public:
  Sphere(const float &radius)
      : Object(
            [this](const float3 &p) { return length(p) - this->radius; }),
        radius(radius) {}
  ~Sphere() {}

  void set_radius(const float &r) { radius = r; }
  float get_radius() const { return radius; }

  float radius;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_SPHERE_HPP_
