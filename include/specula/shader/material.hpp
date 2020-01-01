#ifndef SPECULA_MATERIAL_HPP_
#define SPECULA_MATERIAL_HPP_

#include <memory>

#include <glm/glm.hpp>

namespace specula {
struct Material : public std::enable_shared_from_this<Material> {
  Material();
  glm::vec3 base_color;
  glm::vec3 transmittance_color;
  glm::vec3 emission_color;
  float sheen, sheen_tint;
  float clearcoat, clearcoat_gloss;
  float metallic;
  float spec_trans, diff_trans;
  float flatness;
  float anisotropic;
  float ior;
  float specular_tint;
  float roughness;
  float scatter_distance;
  unsigned long uuid;
};

#define BUILD_VAR(name, type)                                                  \
  inline MaterialBuilder &name(const type &v) {                                \
    data.name = v;                                                             \
    return *this;                                                              \
  }

class MaterialBuilder {
public:
  static inline MaterialBuilder Diffuse() { return MaterialBuilder(); }
  static inline MaterialBuilder Specular() { return MaterialBuilder(); }
  static inline MaterialBuilder Transparent() { return MaterialBuilder(); }
  inline Material build() const { return data; }

  BUILD_VAR(base_color, glm::vec3)
  BUILD_VAR(transmittance_color, glm::vec3)
  BUILD_VAR(emission_color, glm::vec3)
  BUILD_VAR(sheen, float)
  BUILD_VAR(sheen_tint, float)
  BUILD_VAR(clearcoat, float)
  BUILD_VAR(clearcoat_gloss, float)
  BUILD_VAR(metallic, float)
  BUILD_VAR(spec_trans, float)
  BUILD_VAR(diff_trans, float)
  BUILD_VAR(flatness, float)
  BUILD_VAR(anisotropic, float)
  BUILD_VAR(ior, float)
  BUILD_VAR(specular_tint, float)
  BUILD_VAR(roughness, float)
  BUILD_VAR(scatter_distance, float)

private:
  Material data;
};

} // namespace specula

#endif // SPECULA_MATERIAL_HPP_