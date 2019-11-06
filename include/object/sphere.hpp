#ifndef SPECULA_OBJECT_SPHERE_HPP_
#define SPECULA_OBJECT_SPHERE_HPP_

#include <glm/glm.hpp>

#include "object_class.hpp"

namespace specula {
namespace object {
class Sphere : public Object {
public:
  Sphere(const float &radius)
      : Object([this](const glm::vec3 &p) {
          return glm::length(p) - this->radius;
        }) {}
  float radius;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_SPHERE_HPP_
