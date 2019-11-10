#ifndef SPECULA_OBJECT_ROUND_BOX_HPP_
#define SPECULA_OBJECT_ROUND_BOX_HPP_

#define GLM_FORCE_SWIZZLE

#include <glm/glm.hpp>

#include "object_class.hpp"

namespace specula {
namespace object {
class RoundBox : public Object {
public:
  RoundBox(const float &w, const float &h, const float &l, const float &r)
      : Object([this](const glm::vec3 &p) {
          const glm::vec3 d = glm::abs(p) - this->box;
          return glm::length(glm::max(d, 0.0f)) - this->radius +
                 glm::min(glm::max(d.x, glm::max(d.y, d.z)), 0.0f);
        }),
        box(w, h, l), radius(r) {}
  ~RoundBox() {}

  void set_width(const float &w) { box.x = w; }
  float get_width() const { return box.x; }
  void set_height(const float &h) { box.y = h; }
  float get_height() const { return box.y; }
  void set_length(const float &l) { box.z = l; }
  float get_length() const { return box.z; }
  void set_radius(const float &r) { radius = r; }
  float get_radius() const { return radius; }

  glm::vec3 box;
  float radius;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_SPHERE_HPP_
