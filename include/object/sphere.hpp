#ifndef SPECULA_OBJECT_SPHERE_HPP_
#define SPECULA_OBJECT_SPHERE_HPP_

#include "object_class.hpp"
#include "../math/math.hpp"

namespace specula {
namespace object {
class Sphere : public Object {
public:
  Sphere(const float &radius)
      : Object([this](const float3 &p) {
          return this->radius;
          // return glm::length(p) - this->radius;
        }) {}
  float radius;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_SPHERE_HPP_
