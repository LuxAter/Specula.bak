#ifndef SPECULA_OBJECT_PLANE_HPP_
#define SPECULA_OBJECT_PLANE_HPP_

#define GLM_FORCE_SWIZZLE

#include <glm/glm.hpp>

#include "object_class.hpp"

namespace specula {
namespace object {
class Plane : public Object {
public:
  Plane(const float &x, const float &y, const float &z, const float &w)
      : Object([this](const glm::vec3 &p) {
          return glm::dot(p, this->normal.xyz()) + this->normal.w;
        }),
        normal(x, y, z, w) {}
  ~Plane() {}

  float get_x() const { return normal.x; }
  float get_y() const { return normal.y; }
  float get_z() const { return normal.z; }
  float get_w() const { return normal.w; }
  void set_x(const float &v) { normal.x = v; }
  void set_y(const float &v) { normal.y = v; }
  void set_z(const float &v) { normal.z = v; }
  void set_w(const float &v) { normal.w = v; }

  glm::vec4 normal;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_PLANE_HPP_
