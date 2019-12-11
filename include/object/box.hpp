#ifndef SPECULA_OBJECT_BOX_HPP_
#define SPECULA_OBJECT_BOX_HPP_

#include <string>

#include "../math.hpp"
#include "object_class.hpp"

namespace specula::object {
class Box : public ObjectBase, public std::enable_shared_from_this<Box> {
public:
  Box(const float &x, const float &y, const float &z)
      : ObjectBase(
            [this](const glm::vec3 &p) {
              const glm::vec3 q = glm::abs(p) - this->dimensions;
              return glm::length(glm::max(q, 0.0f)) +
                     glm::min(glm::max(q.x, glm::max(q.y, q.z)), 0.0f);
            },
            {{"dimensions", &(this->dimensions)}}),
        dimensions(x, y, z) {}
  Box(const glm::vec3 &dimensions)
      : ObjectBase(
            [this](const glm::vec3 &p) {
              const glm::vec3 q = glm::abs(p) - this->dimensions;
              return glm::length(glm::max(q, 0.0f)) +
                     glm::min(glm::max(q.x, glm::max(q.y, q.z)), 0.0f);
            },
            {{"dimensions", &(this->dimensions)}}),
        dimensions(dimensions) {}
  glm::vec3 dimensions;

  ObjectOperators(Box)
};
} // namespace specula::object

#endif // SPECULA_OBJECT_BOX_HPP_
