#ifndef SPECULA_OBJECT_QUAD_HPP_
#define SPECULA_OBJECT_QUAD_HPP_

#include <glm/glm.hpp>

#include "object_class.hpp"

namespace specula {
namespace object {
class Quad : public Object {
public:
  Quad(const float &ax, const float &ay, const float &az, const float &bx,
       const float &by, const float &bz, const float &cx, const float &cy,
       const float &cz, const float &dx, const float &dy, const float &dz)
      : Object([this](const glm::vec3 &p) {
          auto dot2 = [](const glm::vec3 &v) {
            return glm::dot(v, v);
          };
          const glm::vec3 ba = b - a;
          const glm::vec3 pa = p - a;
          const glm::vec3 cb = c - b;
          const glm::vec3 pb = p - b;
          const glm::vec3 dc = d - c;
          const glm::vec3 pc = p - c;
          const glm::vec3 ad = a - d;
          const glm::vec3 pd = p - d;
          const glm::vec3 nor = glm::cross(ba, ad);

          return glm::sqrt(
              (glm::sign(glm::dot(glm::cross(ba, nor), pa)) +
                   glm::sign(glm::dot(glm::cross(cb, nor), pb)) +
                   glm::sign(glm::dot(glm::cross(dc, nor), pc)) +
                   glm::sign(glm::dot(glm::cross(ad, nor), pd)) <
               3.0)
                  ? glm::min(
                        glm::min(
                            glm::min(
                                dot2(ba * glm::clamp(glm::dot(ba, pa) / dot2(ba),
                                                     0.0f, 1.0f) -
                                     pa),
                                dot2(cb *
                                         glm::clamp(glm::dot(cb, pb) / dot2(cb),
                                                    0.0f, 1.0f) -
                                     pb)),
                            dot2(dc * glm::clamp(glm::dot(dc, pc) / dot2(dc),
                                                 0.0f, 1.0f) -
                                 pc)),
                        dot2(ad * glm::clamp(glm::dot(ad, pd) / dot2(ad), 0.0f,
                                             1.0f) -
                             pd))
                  : glm::dot(nor, pa) * glm::dot(nor, pa) / dot2(nor));
        }),
        a(ax, ay, az), b(bx, by, bz), c(cx, cy, cz), d(dx, dy, dz) {}
  ~Quad() {}

  void set_a(const float &x, const float &y, const float &z) { a = {x, y, z}; }
  glm::vec3 get_a() const { return a; }
  void set_b(const float &x, const float &y, const float &z) { b = {x, y, z}; }
  glm::vec3 get_b() const { return b; }
  void set_c(const float &x, const float &y, const float &z) { c = {x, y, z}; }
  glm::vec3 get_c() const { return c; }
  void set_d(const float &x, const float &y, const float &z) { d = {x, y, z}; }
  glm::vec3 get_d() const { return d; }

  glm::vec3 a, b, c, d;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_SPHERE_HPP_
