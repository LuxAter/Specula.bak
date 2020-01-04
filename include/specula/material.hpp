#ifndef SPECULA_MATERIAL_HPP_
#define SPECULA_MATERIAL_HPP_

#include <memory>

#include <glm/glm.hpp>

#include "builder.hpp"
#include "enum.hpp"
#include "rand.hpp"

namespace specula {
struct Material : public std::enable_shared_from_this<Material> {
  PBUILD_PVAR(Material, glm::vec3, base_color, glm::vec3(0.0f, 0.0f, 0.0f));
  PBUILD_PVAR(Material, float, metallic, 0.0f);
  PBUILD_PVAR(Material, float, transmission, 0.0f);
  PBUILD_PVAR(Material, float, specular, 0.5f);
  PBUILD_PVAR(Material, float, sheen, 0.0f);
  PBUILD_PVAR(Material, float, clearcoat, 0.0f);

public:
  std::size_t uuid = size_rand();
};

std::shared_ptr<Material> Diffuse(const glm::vec3 &color);
} // namespace specula

#endif // SPECULA_MATERIAL_HPP_