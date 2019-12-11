#ifndef SPECULA_OBJECT_TORUS_HPP_
#define SPECULA_OBJECT_TORUS_HPP_

#include <string>

#include "../math.hpp"
#include "object_class.hpp"

namespace specula::object {
class Torus : public ObjectBase, public std::enable_shared_from_this<Torus> {
public:
  Torus(const float &r_rev, const float &r_circ)
      : ObjectBase(
            [this](const glm::vec3 &p) {
              const glm::vec2 q =
                  glm::vec2(glm::length(p.xz()) - this->torus.x, p.y);
              return glm::length(q) - this->torus.y;
            },
            {{"torus", &(this->torus)}}),
        torus(r_rev, r_circ) {}
  Torus(const glm::vec2 &t)
      : ObjectBase(
            [this](const glm::vec3 &p) {
              const glm::vec2 q =
                  glm::vec2(glm::length(p.xz()) - this->torus.x, p.y);
              return glm::length(q) - this->torus.y;
            },
            {{"torus", &(this->torus)}}),
        torus(t) {}
  glm::vec2 torus;

  ObjectOperators(Torus)
};
} // namespace specula::object

#endif // SPECULA_OBJECT_TORUS_HPP_
