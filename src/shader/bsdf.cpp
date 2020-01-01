#include "specula/shader/bsdf.hpp"

#include <memory>

#include <glm/glm.hpp>

#include "specula/ray.hpp"
#include "specula/shader/bsdf.hpp"
#include "specula/shader/fresnel.hpp"
#include "specula/shader/material.hpp"

specula::Ray specula::shader::sample_bsdf(const Ray &in_ray,
                                          const std::shared_ptr<Material> &mat,
                                          const glm::vec3 &normal,
                                          const float &ep) {
  return Ray({glm::vec3(in_ray.o) + ep * normal, glm::vec3(0.0f), nullptr});
}
glm::vec3 specula::shader::evaluate_bsdf(const Ray &ray_in, const Ray &ray_out,
                                         const std::shared_ptr<Material> &mat,
                                         const glm::vec3 &radiance,
                                         const glm::vec3 &normal) {
  return mat->base_color;
}
glm::vec3 specula::shader::calculate_tint(const glm::vec3 &base_color) {
  const float luminance = glm::dot(glm::vec3(0.3f, 0.6f, 1.0f), base_color);
  return (luminance > 0.0f) ? base_color * (1.0f / luminance) : glm::vec3(1.0f);
}
glm::vec3 specula::shader::evaluate_sheen(const std::shared_ptr<Material> &mat,
                                          const glm::vec3 &out,
                                          const glm::vec3 &micro_normal,
                                          const glm::vec3 &in) {
  if (mat->sheen <= 0.0f)
    return glm::vec3(0.0f);
  const float dot_hl = glm::dot(micro_normal, in);
  const glm::vec3 tint = calculate_tint(mat->base_color);
  return mat->sheen * glm::mix(glm::vec3(1.0f), tint, mat->sheen_tint) *
         fresnel::schlick_weight(dot_hl);
}
float specula::shader::gtr1(const float &abs_dot, const float &a) {
  if (a >= 1.0f)
    return 1.0f / M_PI;
  const float a2 = a * a;
  return (a2 - 1.0f) /
         (M_PI * glm::log2(a2) * (1.0f + (a2 - 1.0f) * abs_dot * abs_dot));
}
float specula::shader::separable_smith_ggxg1(const glm::vec3 &w,
                                             const float &a) {
  const float a2 = a * a;
  const float abs_dot = glm::abs(w.y);
  return 2.0f / (1.0f + glm::sqrt(a2 + (1 - a2) * abs_dot * abs_dot));
}
float specula::shader::evaluate_disney_clearcoat(const float &clearcoat,
                                                 const float &alpha,
                                                 const glm::vec3 &out,
                                                 const glm::vec3 &micro_normal,
                                                 const glm::vec3 &in,
                                                 float &f_pdfw, float &r_pdfw) {
  if (clearcoat <= 0.0f)
    return 0.0f;
  const float nh = glm::abs(micro_normal.y);
  const float nl = glm::abs(in.y);
  const float nv = glm::abs(out.y);
  const float hl = glm::dot(micro_normal, in);

  const float d = gtr1(nh, glm::mix(0.1f, 0.001f, alpha));
  const float f = fresnel::schlick(0.04f, hl);
  const float gl = separable_smith_ggxg1(in, 0.25f);
  const float gv = separable_smith_ggxg1(out, 0.25f);

  f_pdfw = d / (4.0f * nl);
  r_pdfw = d / (4.0f * nv);
  return 0.25f * clearcoat * d * f * gl * gv;
}
float specula::shader::ggx_anisotropic_d(const glm::vec3 &micro_normal,
                                         const float &ax, const float &ay) {
  const float hx2 = micro_normal.x * micro_normal.x;
  const float hy2 = micro_normal.z * micro_normal.z;
  const float cos2_theta = micro_normal.y * micro_normal.y;
  const float ax2 = ax * ax;
  const float ay2 = ay * ay;
  const float tmp = hx2 / ax2 + hy2 / ay2 + cos2_theta;
  return 1.0f / (M_PI * ax * ay * tmp * tmp);
}
float specula::shader::separable_smith_ggxg1(const glm::vec3 &omega,
                                             const glm::vec3 &micro_normal,
                                             const float &ax, const float &ay) {
  const float hw = glm::dot(omega, micro_normal);
  if (hw <= 0.0f)
    return 0.0f;
  const float abs_tan_theta = glm::abs()
}