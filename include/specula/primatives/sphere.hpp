#ifndef SPHERE_HPP_TGCSKSOZ
#define SPHERE_HPP_TGCSKSOZ

#define GLM_FORCE_SWIZZLE
#include "../object.hpp"

namespace specula {
Object Sphere(const float &r) {
  return Object(
      [](const Object *obj, const glm::vec3 &p) {
        return glm::length(p) - std::get<float>(obj->variables.at("radius"));
      },
      "return length(p) - {{ radius }};", {{"radius", r}});
}
} // namespace specula

#endif /* end of include guard: SPHERE_HPP_TGCSKSOZ */
