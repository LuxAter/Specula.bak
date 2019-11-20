#ifndef SPECULA_OBJECT_TORUS_HPP_
#define SPECULA_OBJECT_TORUS_HPP_

#include <glm/glm.hpp>

#include "object_class.hpp"

namespace specula {
namespace object {
class Torus : public Object {
public:
  Torus(const float &radius_big, const float &radius_small)
      : Object([this](const glm::vec3 &p) {
          const glm::vec2 q = glm::vec2(glm::length(p.xz()) - this->torus.x, p.y);
          return glm::length(q) - this->torus.y;
        }),
        torus(radius_big, radius_small) {}
  ~Torus() {}

  void set_radius_big(const float &r) { torus.x = r; }
  float get_radius_big() const { return torus.x; }
  void set_radius_small(const float &r) { torus.y = r; }
  float get_radius_small() const { return torus.y; }

  glm::vec2 torus;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_TORUS_HPP_
