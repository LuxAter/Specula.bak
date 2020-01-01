#ifndef SPECULA_FRESNEL_HPP_
#define SPECULA_FRESNEL_HPP_

namespace specula {
namespace fresnel {
float schlick_weight(const float &dot);
glm::vec3 schlick(const glm::vec3 &r0, const float &radians);
float schlick(const float &r0, const float &radians);
} // namespace fresnel
} // namespace specula

#endif // SPECULA_FRESNEL_HPP_