#ifndef SPECULA_BSDF_HPP_
#define SPECULA_BSDF_HPP_

#include <memory>

#include <glm/glm.hpp>

#include "../ray.hpp"
#include "material.hpp"

namespace specula {
namespace shader {
Ray sample_bsdf(const Ray &in_ray, const std::shared_ptr<Material> &mat,
                const glm::vec3 &normal, const float &ep);
glm::vec3 evaluate_bsdf(const Ray &ray_in, const Ray &ray_out,
                        const std::shared_ptr<Material> &mat,
                        const glm::vec3 &radiance, const glm::vec3 &normal);
glm::vec3 calculate_tint(const glm::vec3 &base_color);
glm::vec3 evaluate_sheen(const std::shared_ptr<Material> &mat,
                         const glm::vec3 &out, const glm::vec3 &micro_normal,
                         const glm::vec3 &in);
float gtr1(const float &abs_dot, const float &a);
float separable_smith_ggxg1(const glm::vec3 &w, const float &a);
float evaluate_disney_clearcoat(const float &clearcoat, const float &alpha,
                                const glm::vec3 &out,
                                const glm::vec3 &micro_normal,
                                const glm::vec3 &in, float &f_pdfw,
                                float &r_pdfw);
float ggx_anisotropic_d(const glm::vec3 &micro_normal, const float &ax,
                        const float &ay);
float separable_smith_ggxg1(const glm::vec3 &omega,
                            const glm::vec3 &micro_normal, const float &ax,
                            const float &ay);
} // namespace shader
} // namespace specula

#endif // SPECULA_BSDF_HPP_