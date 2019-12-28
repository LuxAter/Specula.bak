#ifndef SPECULA_BSDF_HPP_
#define SPECULA_BSDF_HPP_

#include <memory>

#include <glm/glm.hpp>

#include "material.hpp"

namespace specula {
namespace shader {
glm::vec3 sample_bsdf(const std::shared_ptr<Material> &medium,
                      const std::shared_ptr<Material> &mat,
                      const glm::vec3 &dir, const glm::vec3 &normal);
} // namespace shader
} // namespace specula

#endif // SPECULA_BSDF_HPP_