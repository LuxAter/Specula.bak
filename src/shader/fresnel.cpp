#include "specula/shader/fresnel.hpp"

#include <glm/glm.hpp>

float specula::fresnel::schlick_weight(const float &u) {
  const float m = glm::clamp(1.0f - u, 0.0f, 1.0f);
  const float m2 = m * m;
  return m * m2 * m2;
}
glm::vec3 specula::fresnel::schlick(const glm::vec3 &r0, const float &radians) {
  const float exponential = glm::pow(1.0f - radians, 5.0f);
  return r0 + (glm::vec3(1.0f) - r0) * exponential;
}
float specula::fresnel::schlick(const float &r0, const float &radians) {
  return glm::mix(1.0f, schlick_weight(radians), r0);
}