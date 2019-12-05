#ifndef SPECULA_OBJECT_SPHERE_HPP_
#define SPECULA_OBJECT_SPHERE_HPP_

#include <string>

#include "../math.hpp"
#include "object_class.hpp"

namespace specula::object {
class Sphere : public ObjectBase, public std::enable_shared_from_this<Sphere> {
public:
  Sphere(const float &radius)
      : ObjectBase(
            [this](const glm::vec3 &p) {
              return glm::length(p) - this->radius;
            },
            "return length(p) - {{ radius }}", {{"radius", &(this->radius)}}),
        radius(radius) {}
  float radius;

  ObjectOperators(Sphere)
};
} // namespace specula::object

#endif // SPECULA_OBJECT_SPHERE_HPP_
