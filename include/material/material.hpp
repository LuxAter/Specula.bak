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
  float ior;
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
  Material &set_emission(const float& _emission) {
    emission = _emission;
    return *this;
  }
  Material &set_ior(const float& _ior) {
    ior = _ior;
    return *this;
  }
};
} // namespace material
} // namespace specula

#endif // SPECULA_MATERIAL_HPP_
