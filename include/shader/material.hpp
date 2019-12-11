#ifndef SPECULA_MATERIAL_HPP_
#define SPECULA_MATERIAL_HPP_

#include <memory>

#include "../math.hpp"

namespace specula {
class Material : public std::enable_shared_from_this<Material> {
public:
  enum Type { EMISSIVE, DIFFUSE, SPECULAR, TRANSPARENT };

  Material(const Type &type)
      : type(type), base_color(0.0f), emission(0.0f), ior(1.0f) {}
  Material(const Type &type, const glm::vec3 &base_color, const float &emission,
           const float &ior)
      : type(type), base_color(base_color), emission(emission), ior(ior) {}
  inline static std::shared_ptr<Material> Emissive(const float &emmisive,
                                                   float r = 1.0f,
                                                   float g = 1.0f,
                                                   float b = 1.0f) {
    return std::make_shared<Material>(EMISSIVE, glm::vec3(r, g, b), emmisive,
                                      1.0f);
  }
  inline static std::shared_ptr<Material>
  Emissive(float emmisive = 1.0f, glm::vec3 base_color = glm::vec3(1.0f)) {
    return std::make_shared<Material>(EMISSIVE, base_color, emmisive, 1.0f);
  }
  inline static std::shared_ptr<Material>
  Diffuse(const float &r, const float &g, const float &b) {
    return std::make_shared<Material>(DIFFUSE, glm::vec3(r, g, b), 0.0f, 1.0f);
  }
  inline static std::shared_ptr<Material>
  Diffuse(glm::vec3 base_color = glm::vec3(1.0f)) {
    return std::make_shared<Material>(DIFFUSE, base_color, 0.0f, 1.0f);
  }
  inline static std::shared_ptr<Material> Specular() {
    return std::make_shared<Material>(SPECULAR, glm::vec3(0.0f), 0.0f, 1.0f);
  }
  inline static std::shared_ptr<Material> Transparent(float ior = 1.0f) {
    return std::make_shared<Material>(TRANSPARENT, glm::vec3(0.0f), 0.0f, ior);
  }

  Type type;
  glm::vec3 base_color;
  float emission;
  float ior;

  std::shared_ptr<Material> set_type(const Type &tp) {
    type = tp;
    return shared_from_this();
  }
  std::shared_ptr<Material> set_color(const float &r, const float &g,
                                      const float &b) {
    base_color = {r, g, b};
    return shared_from_this();
  }
  std::shared_ptr<Material> set_color(const glm::vec3 &c) {
    base_color = c;
    return shared_from_this();
  }
  std::shared_ptr<Material> set_emission(const float &v) {
    emission = v;
    return shared_from_this();
  }
  std::shared_ptr<Material> set_ior(const float &v) {
    ior = v;
    return shared_from_this();
  }
};
} // namespace specula

#endif // SPECULA_MATERIAL_HPP_
