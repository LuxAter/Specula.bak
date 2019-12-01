#ifndef SPECULA_MATERIAL_HPP_
#define SPECULA_MATERIAL_HPP_

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>

#include "../rand.hpp"

namespace specula {
namespace material {
enum Type { DIFFUSE, SPECULAR, REFRACTIVE };
struct Material {
  Material(const Type &type, const glm::vec3 &color, const float &emission,
           const float &ior)
      : type(type), base_color(color), emission(emission), ior(ior),
        uuid_(rand::urand()) {}
  Type type;
  glm::vec3 base_color;
  float emission;
  float ior;
  std::size_t uuid_;
  Material &set_color(const float &r, const float &g, const float &b) {
    base_color = {r, g, b};
    return *this;
  }
  Material &set_type(const Type &_type) {
    type = _type;
    return *this;
  }
  Material &set_emission(const float &_emission) {
    emission = _emission;
    return *this;
  }
  Material &set_ior(const float &_ior) {
    ior = _ior;
    return *this;
  }
};
} // namespace material
} // namespace specula

#endif // SPECULA_MATERIAL_HPP_
