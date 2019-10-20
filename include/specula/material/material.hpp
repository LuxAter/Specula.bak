#ifndef SPECULA_MATERIAL_MATERIAL_HPP_
#define SPECULA_MATERIAL_MATERIAL_HPP_

#include <array>

#include <glm/glm.hpp>

namespace specula {
class Material {
public:
  Material() {}
  virtual ~Material() {}

  glm::vec3 base_color;

  float subsurface;
  glm::vec3 subsurface_radius;
  glm::vec3 subsurface_color;

  float metallic;
  float specular;
  float specular_tint;
  float roughness;

  float sheen, sheen_tint;

  float clearcoat, clearcoat_roughness;

  float ior;
  float transmission;
  float transmission_roughness;

  float emission;

private:
};
} // namespace specula

#endif // SPECULA_MATERIAL_MATERIAL_HPP_
