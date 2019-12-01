#ifndef SPECULA_OBJECT_SPHERE_HPP_
#define SPECULA_OBJECT_SPHERE_HPP_

#include <string>

#include "../math.hpp"
#include "object_class.hpp"

#include "../scene.hpp"

namespace specula {
class Sphere : public ObjectBase {
public:
  Sphere(const float &radius)
      : ObjectBase(
            [this](const glm::vec3 &p) {
              return glm::length(p) - this->radius;
            },
            "return length(p) - {{ radius }}", {{"radius", &(this->radius)}}),
        radius(radius) {
    scene::objects.push_back(std::shared_ptr<Sphere>(this));
  }
  float radius;
};
} // namespace specula

#endif // SPECULA_OBJECT_SPHERE_HPP_
