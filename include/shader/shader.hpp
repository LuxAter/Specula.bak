#ifndef SPECULA_SHADER_HPP_
#define SPECULA_SHADER_HPP_

#include <memory>
#include <tuple>

#include <glm/glm.hpp>

#include "../material/material.hpp"

namespace specula {
namespace shader {
namespace fresnel {
  float schlick(const float& r0, const float& radians);
} // namespace fresnel
namespace bsdf {
  float separable_smith_ggxg1(const float& nv, const float& a);
} // namespace bsdf
struct Angles {
  float nh, nl, nv, hl;
};
std::tuple<glm::vec3, glm::vec3> make_ortho_coord_sys(const glm::vec3 &v1);

// std::tuple<float, float, float, float>
// calculate_lobe_pdfs(const std::shared_ptr<material::Material> &mat);
// float thin_transmission_roughness(
//     const std::shared_ptr<material::Material> &mat);
// std::tuple<float, float>
// calculate_anisotropic_params(const std::shared_ptr<material::Material> &mat);
// float gtr1(const float& hl, const float& a);
//
// std::tuple<float, float, float>
// evaluate_clearcoat(const std::shared_ptr<material::Material> &mat,
//                    const glm::vec3 &v, const glm::vec3 &h, const glm::vec3 &l,
//                    const Angles &angle);
//
// glm::vec3 evaluate(const glm::vec3 &pos, const glm::vec3 &normal,
//                    const glm::mat3 &world_to_tangent, const glm::vec3 &v,
//                    const glm::vec3 &l,
//                    const std::shared_ptr<material::Material> &mat,
//                    const bool &thin, float &forward_pdf, float &reverse_pdf);
} // namespace shader
} // namespace specula

#endif // SPECULA_SHADER_HPP_
