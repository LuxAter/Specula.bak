#ifndef SPECULA_OBJECT_BOX_HPP_
#define SPECULA_OBJECT_BOX_HPP_

#include <glm/glm.hpp>

#include "object_class.hpp"

namespace specula {
namespace object {
class Box : public Object {
public:
  Box(const float &w, const float &h, const float &l)
      : Object([this](const glm::vec3 &p) {
          const glm::vec3 d = glm::abs(p) - this->box;
          return glm::length(glm::max(d, 0.0f)) +
                 glm::min(glm::max(d.x, glm::max(d.y, d.z)), 0.0f);
        }),
        box(w, h, l) {}
  ~Box() {}

  void set_width(const float &w) { box.x = w; }
  float get_width() const { return box.x; }
  void set_height(const float &h) { box.y = h; }
  float get_height() const { return box.y; }
  void set_length(const float &l) { box.z = l; }
  float get_length() const { return box.z; }

  glm::vec3 box;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_SPHERE_HPP_
