#ifndef SPECULA_MATERIAL_HPP_
#define SPECULA_MATERIAL_HPP_

#include <memory>

#include <glm/glm.hpp>

#include "builder.hpp"
#include "enum.hpp"
#include "rand.hpp"

namespace specula {
ENUM(NormalDistributionFunction, D_BLINN_PHONG, D_BECKMANN, D_GGX,
     D_GGX_ANISOTROPIC);
ENUM(GeometricShading, G_IMPLICIT, G_NEUMANN, G_COOK_TORRANCE, G_KELEMEN,
     G_BECKMANN, G_BLINN_PHONG, G_GGX, G_SCHLICK_BECKMANN, G_SCHLICK_GGX);
ENUM(Fresnel, F_NONE, F_SCHLICK, F_COOK_TORANCE);

struct Material : public std::enable_shared_from_this<Material> {
  PBUILD_PVAR(Material, glm::vec3, base_color, glm::vec3(0.0f, 0.0f, 0.0f));
  PBUILD_PVAR(Material, float, subsurface, 0.0f);
  PBUILD_PVAR(Material, float, metallic, 0.0f);
  PBUILD_PVAR(Material, float, specular, 0.5f);
  PBUILD_PVAR(Material, float, specular_tint, 0.0f);
  PBUILD_PVAR(Material, float, roughness, 0.5f);
  PBUILD_PVAR(Material, float, anisotropic, 0.0f);
  PBUILD_PVAR(Material, float, sheen, 0.0f);
  PBUILD_PVAR(Material, float, sheen_tint, 0.5f);
  PBUILD_PVAR(Material, float, clearcoat, 0.0f);
  PBUILD_PVAR(Material, float, clearcoat_roughness, 0.03f);

  PBUILD_PVAR(Material, float, ior, 1.450f);
  PBULID_PVAR(Material, float, transmission, 0.0f);

  PBUILD_PVAR(Material, NormalDistributionFunction, normal_distrobution,
              D_GGX_ANISOTROPIC);
  PBUILD_PVAR(Material, GeometricShading, geometric_shading, G_GGX);
  PBUILD_PVAR(Material, Fresnel, fresnel, F_SCHLICK);

public:
  std::size_t uuid = size_rand();
};

std::shared_ptr<Material> Diffuse(const glm::vec3 &color);
} // namespace specula

#endif // SPECULA_MATERIAL_HPP_
