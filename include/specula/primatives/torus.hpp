#ifndef TORUS_HPP_W5XJMAN7
#define TORUS_HPP_W5XJMAN7

#define GLM_FORCE_SWIZZLE
#include "../object.hpp"

namespace specula {
Object Torus(const float &rad_rev, const float &r) {
  return Object(
      [](const Object *obj, const glm::vec3 &p) {
        const glm::vec2 q =
            glm::vec2(glm::length(p.xz()) -
                          std::get<float>(obj->variables.at("radius_rev")),
                      p.y);
        return glm::length(q) - std::get<float>(obj->variables.at("radius"));
      },
      "const float2 q = (float2)(length(p.xz) - {{ radius_rev }}, p.y); return "
      "length(q) - {{ radius }};",
      {{"radius_rev", rad_rev}, {"radius", r}});
}
} // namespace specula

#endif /* end of include guard: TORUS_HPP_W5XJMAN7 */
