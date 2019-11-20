#include "shader/shader.hpp"

#include <memory>
#include <tuple>

#include <glm/glm.hpp>

#include "material/material.hpp"
#include "math.hpp"

float specula::shader::fresnel::schlick(const float &r0, const float &radians) {
  float m = glm::clamp(1.0f - radians, 0.0f, 1.0f);
  float m2 = m * m;
  return glm::lerp(1.0f, m * m2 * m2, r0);
}

float specula::shader::bsdf::separable_smith_ggxg1(const float &nv,
                                                   const float &a) {
  float a2 = a * a;
  return 2.0f / (1.0f + glm::sqrt(a2 + (1 - a2) * nv * nv));
}

std::tuple<glm::vec3, glm::vec3>
specula::shader::make_ortho_coord_sys(const glm::vec3 &v1) {
  glm::vec3 v2, v3;
  if (glm::abs(v1.x) > glm::abs(v1.y))
    v2 = glm::vec3(-v1.z, 0.0f, v1.x) *
         (1.0f / glm::sqrt(v1.x * v1.x + v1.z * v1.z));
  else
    v2 = glm::vec3(0.0f, v1.z, -v1.y) *
         (1.0f / glm::sqrt(v1.y * v1.y + v1.z * v1.z));
  v3 = glm::cross(v1, v2);
  return std::make_tuple(v2, v3);
}

// std::tuple<float, float, float, float> specula::shader::calculate_lobe_pdfs(
//     const std::shared_ptr<material::Material> &mat) {
//   float metallic_brdf = mat->metallic;
//   float specular_bsdf = (1.0f - mat->metallic) * mat->spec_trans;
//   float dielectric_brdf = (1.0f - mat->spec_trans) * (1.0f - mat->metallic);
//
//   float specular_weight = metallic_brdf + dielectric_brdf;
//   float transmission_weight = specular_bsdf;
//   float diffuse_weight = dielectric_brdf;
//   float clearcoat_weight = 1.0f * glm::clamp(mat->clearcoat, 0.0f, 1.0f);
//
//   float norm = 1.0f / (specular_weight + transmission_weight + diffuse_weight +
//                        clearcoat_weight);
//
//   return std::make_tuple(specular_weight * norm, diffuse_weight * norm,
//                          clearcoat_weight * norm, transmission_weight * norm);
// }
//
// float specula::shader::thin_transmission_roughness(
//     const std::shared_ptr<material::Material> &mat) {
//   return glm::clamp((0.65f * mat->ior - 0.35f) * mat->roughness, 0.0f, 1.0f);
// }
//
// std::tuple<float, float> specula::shader::calculate_anisotropic_params(
//     const std::shared_ptr<material::Material> &mat) {
//   float aspect = glm::sqrt(1.0f - 0.9f * mat->anisotropic);
//   return std::make_tuple(
//       glm::max(0.001f, mat->roughness * mat->roughness / aspect),
//       glm::max(0.00f, mat->roughness * mat->roughness * aspect));
// }
//
// float specula::shader::gtr1(const float &hl, const float &a) {
//   if (a >= 1) {
//     return 1.0f / static_cast<float>(M_PI);
//   }
//   float a2 = a * a;
//   return (a2 - 1.0f) / (M_PI * glm::log2(a2) * (1.0f + (a2 - 1.0f) * hl * hl));
// }
//
// std::tuple<float, float, float> specula::shader::evaluate_clearcoat(
//     const std::shared_ptr<material::Material> &mat, const glm::vec3 &v,
//     const glm::vec3 &h, const glm::vec3 &l, const Angles &angle) {
//   if (mat->clearcoat <= 0.0f) {
//     return std::make_tuple(0.0f, 0.0f, 0.0f);
//   }
//   float abs_nh = glm::abs(angle.nh);
//   float abs_nl = glm::abs(angle.nl);
//   float abs_nv = glm::abs(angle.nv);
//
//   float d = gtr1(abs_nh, glm::lerp(0.1f, 0.001f, mat->clearcoat_gloss));
//   float f = fresnel::schlick(0.04f, angle.hl);
//   float gl = bsdf::separable_smith_ggxg1(abs_nl, 0.25f);
//   float gv = bsdf::separable_smith_ggxg1(abs_nv, 0.25f);
//
//   return std::make_tuple(0.25f * mat->clearcoat * d * f * gl * gv,
//                          d / (4.0f * glm::abs(glm::dot(v, h))),
//                          d / (4.0f * glm::abs(glm::dot(l, h))));
// }
//
// glm::vec3 specula::shader::evaluate(
//     const glm::vec3 &pos, const glm::vec3 &normal,
//     const glm::mat3 &world_to_tangent, const glm::vec3 &v, const glm::vec3 &l,
//     const std::shared_ptr<material::Material> &mat, const bool &thin,
//     float &forward_pdf, float &reverse_pdf) {
//
//   glm::vec3 h = glm::normalize(l + v);
//   Angles angle{glm::dot(normal, v), glm::dot(normal, l), glm::dot(normal, h),
//                glm::dot(h, l)};
//
//   glm::vec3 reflectance(0.0f);
//   forward_pdf = 0.0f;
//   reverse_pdf = 0.0f;
//
//   auto [p_brdf, p_diffuse, p_clearcoat, p_spec_trans] =
//       calculate_lobe_pdfs(mat);
//
//   float metallic = mat->metallic;
//   float spec_trans = mat->spec_trans;
//
//   auto [ax, ay] = calculate_anisotropic_params(mat);
//
//   float diffuse_weight = (1.0f - metallic) * (1.0f - spec_trans);
//   float trans_weight = (1.0f - metallic) * spec_trans;
//
//   bool upper_hemisphere = glm::sign(angle.nl) == glm::sign(angle.nv);
//   if (upper_hemisphere && mat->clearcoat > 0.0f) {
//     auto [clearcoat, forward_clearcoat_pdfw, reverse_clearcoat_pdfw] =
//         evaluate_clearcoat(mat, v, h, l, angle);
//     reflectance += glm::vec3(clearcoat);
//     forward_pdf += p_clearcoat * forward_clearcoat_pdfw;
//     reverse_pdf += p_clearcoat * reverse_clearcoat_pdfw;
//   }
// }
