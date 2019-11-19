#ifndef SPECULA_OBJECT_ROUND_CYLINDER_HPP_
#define SPECULA_OBJECT_ROUND_CYLINDER_HPP_

#include <glm/glm.hpp>

#include "object_class.hpp"

namespace specula {
namespace object {
class RoundCylinder : public Object {
public:
  RoundCylinder(const float &height, const float &radius,
                const float &round_radius)
      : Object([this](const glm::vec3 &p) {
          const glm::vec2 d(glm::length(p.xz()) - 2.0 * this->radius +
                                this->round_radius,
                            glm::abs(p.y) - this->height);
          return glm::min(glm::max(d.x, d.y), 0.0f) +
                 glm::length(glm::max(d, 0.0f)) - this->round_radius;
        }),
        height(height), radius(radius), round_radius(round_radius) {}
  ~RoundCylinder() {}

  void set_height(const float &h) { height = h; }
  float get_height() const { return height; }
  void set_radius(const float &r) { radius = r; }
  float get_radius() const { return radius; }
  void set_round_radius(const float &r) { round_radius = r; }
  float get_round_radius() const { return round_radius; }

  float height, radius, round_radius;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_ROUND_CYLINDER_HPP_
