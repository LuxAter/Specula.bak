#ifndef SPECULA_SHADER_HPP_
#define SPECULA_SHADER_HPP_

#include <memory>
#include <tuple>

#include <glm/glm.hpp>

#include "../material/material.hpp"
#include "../ray.hpp"

namespace specula {
namespace shader {
std::tuple<glm::vec3, glm::vec3> make_ortho_coord_sys(const glm::vec3 &v1);
ray sample_bsdf(const glm::vec4 &p, const ray &out, const glm::vec3 &normal,
                const std::shared_ptr<material::Material> &mat,
                const float &ep);
std::string
generate_sample_kernel(const std::shared_ptr<material::Material> &mat,
                       const float &ep);
glm::vec3 evaluate(const glm::vec4 &p, const ray &out, const ray &incident,
                   const glm::vec3 &normal, const glm::vec3 &incoming,
                   const std::shared_ptr<material::Material> &mat);
std::string generate_evaluate_kernel(const std::shared_ptr<material::Material>& mat);
} // namespace shader
} // namespace specula

#endif // SPECULA_SHADER_HPP_
