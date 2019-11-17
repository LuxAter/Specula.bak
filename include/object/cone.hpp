#ifndef SPECULA_OBJECT_CONE_HPP_
#define SPECULA_OBJECT_CONE_HPP_

#include <glm/glm.hpp>

#include "object_class.hpp"

namespace specula {
namespace object {
class Cone : public Object {
public:
  Cone(const float &height, const float &radius_bottom, const float &radius_top)
      : Object([this](const glm::vec3 &p) {
          const glm::vec2 q(glm::length(p.xz()), p.y);
          const glm::vec2 k1(this->radius_top, this->height);
          const glm::vec2 k2(this->radius_top - this->radius_bottom,
                             2.0f * this->height);
          const glm::vec2 ca(q.x - glm::min(q.x, (q.y < 0.0)
                                                     ? this->radius_bottom
                                                     : this->radius_top),
                             glm::abs(q.y) - this->height);
          const glm::vec2 cb =
              q - k1 +
              k2 * glm::clamp(glm::dot(k1 - q, k2) / glm::dot(k2, k2), 0.0f,
                              1.0f);
          const float s = (cb.x < 0.0 && ca.y < 0.0) ? -1.0 : 1.0;
          return s * glm::sqrt(glm::min(glm::dot(ca, ca), glm::dot(cb, cb)));
        }),
        height(height), radius_bottom(radius_bottom), radius_top(radius_top) {}
  ~Cone() {}

  void set_height(const float &h) { height = h; }
  float get_height() const { return height; }
  void set_radius_bottom(const float &r) { radius_bottom = r; }
  float get_radius_bottom() const { return radius_bottom; }
  void set_radius_top(const float &r) { radius_top = r; }
  float get_radius_top() const { return radius_top; }

  float height, radius_bottom, radius_top;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_CONE_HPP_
