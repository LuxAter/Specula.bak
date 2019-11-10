#ifndef SPECULA_MATERIAL_HPP_
#define SPECULA_MATERIAL_HPP_

#include <glm/glm.hpp>

namespace specula {
namespace material {
enum Type { DIFFUSE, SPECULAR, REFRACTIVE };
struct Material {
  Material(const Type &type, const glm::vec3 &color, const float &emission,
           const float &ior)
      : type(type), base_color(color), emission(emission), ior(ior) {}
  Type type;
  glm::vec3 base_color;
  float emission;
  // float sheen, sheen_tint;
  // float clearcoat, clearcoat_gloss;
  // float metallic;
  // float spec_trans;
  // float diff_trans;
  // float flatness;
  // float anisotropic;
  float ior;
  // float specular_tint;
  // float roughness;
  // float scatter_distance;
  float get_r() { return base_color.r; }
  float get_g() { return base_color.g; }
  float get_b() { return base_color.b; }
  Material &set_color(const float &r, const float &g, const float &b) {
    base_color = {r, g, b};
    return *this;
  }
  Material &set_type(const Type &_type) {
    type = _type;
    return *this;
  }
};
} // namespace material
} // namespace specula

#endif // SPECULA_MATERIAL_HPP_
