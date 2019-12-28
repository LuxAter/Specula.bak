#include <specula/object.hpp>
#include <specula/primatives.hpp>

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>

specula::Object specula::Sphere(const float &r) {
  return Object(
      [](const Object *obj, const glm::vec3 &p) {
        return glm::length(p) - std::get<float>(obj->variables.at("radius"));
      },
      "return length(p) - {{ radius }};", {{"radius", r}});
}
specula::Object specula::Torus(const float &rad_rev, const float &r) {
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