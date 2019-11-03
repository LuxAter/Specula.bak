#ifndef SPECULA_MATERIAL_BSDF_HPP_
#define SPECULA_MATERIAL_BSDF_HPP_

#include <memory>

#include <glm/glm.hpp>

#include "material.hpp"

namespace specula {
namespace bsdf {
glm::vec3 eval(const std::shared_ptr<Material> &mat, const glm::vec3 &l,
               const glm::vec3 &v, const glm::vec3 &n);
} // namespace bsdf
} // namespace specula

#endif // SPECULA_MATERIAL_BSDF_HPP_
