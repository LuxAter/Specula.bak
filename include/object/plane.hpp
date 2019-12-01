#ifndef SPECULA_OBJECT_PLANE_HPP_
#define SPECULA_OBJECT_PLANE_HPP_

#include <string>

#include "../math.hpp"
#include "object_class.hpp"

#include "../scene.hpp"

namespace specula {
class Plane : public ObjectBase {
public:
  Plane(const float &x, const float &y, const float &z, const float &w)
      : ObjectBase(
            [this](const glm::vec3 &p) {
              return glm::dot(p, this->normal.xyz()) + this->normal.w;
            },
            "return dot(p, {{ normal.xyz }}) + {{ normal.w }}",
            {{"normal", &(this->normal)}}),
        normal(x, y, z, w) {
    scene::objects.push_back(std::shared_ptr<Plane>(this));
  }
  Plane(const glm::vec4 &normal)
      : ObjectBase(
            [this](const glm::vec3 &p) {
              return glm::dot(p, this->normal.xyz()) + this->normal.w;
            },
            "return dot(p, {{ normal.xyz }}) + {{ normal.w }}",
            {{"normal", &(this->normal)}}),
        normal(normal) {
    scene::objects.push_back(std::shared_ptr<Plane>(this));
  }
  glm::vec4 normal;
};
} // namespace specula

#endif // SPECULA_OBJECT_PLANE_HPP_
