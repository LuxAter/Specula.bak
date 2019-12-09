#ifndef SPECULA_SHADER_HPP_
#define SPECULA_SHADER_HPP_

#include <memory>

#include "../math.hpp"
#include "material.hpp"

namespace specula {
glm::vec3 sample_bsdf(const std::shared_ptr<Material> &medium,
                      const std::shared_ptr<Material> &mat, const glm::vec3 &lo,
                      const glm::vec3 &n);
glm::vec3 evaluate_bsdf(const std::shared_ptr<Material> &mat,
                        const glm::vec3 &ri, const glm::vec3 &li,
                        const glm::vec3 &lo, const glm::vec3 &n);
} // namespace specula

#endif // SPECULA_SHADER_HPP_
