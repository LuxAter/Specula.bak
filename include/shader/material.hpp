#ifndef SPECULA_MATERIAL_HPP_
#define SPECULA_MATERIAL_HPP_

#include "../math.hpp"

namespace specula {
class Material {
public:
  enum Type { EMISSIVE, DIFFUSE, SPECULAR, TRANSPARENT };

  Material(const Type &type)
      : type(type), base_color(0.0f), emission(0.0f), ior(1.0f) {}
  Material(const Type &type, const glm::vec3 &base_color, const float &emission,
           const float &ior)
      : type(type), base_color(base_color), emission(emission), ior(ior) {}
  inline static Material Emissive(const float &emmisive, float r = 1.0f,
                                  float g = 1.0f, float b = 1.0f) {
    return Material(EMISSIVE, glm::vec3(r, g, b), emmisive, 1.0f);
  }
  inline static Material Emissive(float emmisive = 1.0f,
                                  glm::vec3 base_color = glm::vec3(1.0f)) {
    return Material(EMISSIVE, base_color, emmisive, 1.0f);
  }
  inline static Material Diffuse(const float &r, const float &g,
                                 const float &b) {
    return Material(DIFFUSE, glm::vec3(r, g, b), 0.0f, 1.0f);
  }
  inline static Material Diffuse(glm::vec3 base_color = glm::vec3(1.0f)) {
    return Material(DIFFUSE, base_color, 0.0f, 1.0f);
  }
  inline static Material Specular() {
    return Material(SPECULAR, glm::vec3(0.0f), 0.0f, 1.0f);
  }
  inline static Material Transparent(float ior = 1.0f) {
    return Material(SPECULAR, glm::vec3(0.0f), 0.0f, ior);
  }

  Type type;
  glm::vec3 base_color;
  float emission;
  float ior;

  Material &set_type(const Type &tp) {
    type = tp;
    return *this;
  }
  Material &set_color(const float &r, const float &g, const float &b) {
    base_color = {r, g, b};
    return *this;
  }
  Material &set_color(const glm::vec3 &c) {
    base_color = c;
    return *this;
  }
  Material &set_emission(const float &v) {
    emission = v;
    return *this;
  }
  Material &set_ior(const float &v) {
    ior = v;
    return *this;
  }
};
} // namespace specula

#endif // SPECULA_MATERIAL_HPP_
