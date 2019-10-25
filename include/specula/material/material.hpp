#ifndef SPECULA_MATERIAL_MATERIAL_HPP_
#define SPECULA_MATERIAL_MATERIAL_HPP_

#include <array>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

namespace specula {
class Material {
public:
  Material() {}
  Material(const glm::vec3 &color, const float &metallic, const float &specular,
           const float &specular_tint, const float &roughness,
           const float &sheen, const float &sheen_tint, const float &ior,
           const float &transmission, const float &transmission_roughness,
           const float &emission)
      : base_color(color), metallic(metallic), specular(specular),
        specular_tint(specular_tint), roughness(roughness), sheen(sheen),
        sheen_tint(sheen_tint), ior(ior), transmission(transmission),
        transmission_roughness(transmission_roughness), emission(emission) {}
  virtual ~Material() {}

  inline glm::vec3 bsdf(const glm::vec3 &l, const glm::vec3 &v,
                        const glm::vec3 &n) const {
    const glm::vec3 h = glm::normalize(l + v);
    const float theta_l = glm::dot(l, n), theta_v = glm::dot(n, v),
                theta_d = glm::dot(v, h), theta_h = glm::dot(n, h);
    const float RR = 2.0 * roughness*std::pow(std::cos(theta_d), 2.0);
    const float FL = std::pow(1.0f-std::cos(theta_l), 5.0);
    const float FV = std::pow(1.0f-std::cos(theta_v), 5.0);
    glm::vec3 f_lambert = base_color / (float)M_PI;
    glm::vec3 f_retro_reflection = base_color/(float)M_PI*RR*(FL+FV+FL*FV*(RR-1.0f));
    glm::vec3 fd = f_lambert*(1.0f-0.5f*FL)*(1.0f-0.5f*FV)+f_retro_reflection;
    glm::vec3 fr, ft;
    return fd + fr + ft;
  }

  glm::vec3 base_color;

  // float subsurface;
  // glm::vec3 subsurface_radius;
  // glm::vec3 subsurface_color;

  float metallic;
  float specular;
  float specular_tint;
  float roughness;

  float sheen, sheen_tint;

  // float clearcoat, clearcoat_roughness;

  float ior;
  float transmission;
  float transmission_roughness;

  float emission;

private:
};

class LuaMaterial {
public:
  std::shared_ptr<Material> base_;
};

inline LuaMaterial gen_LuaMaterial(
    const glm::vec3 &color, const float &metallic, const float &specular,
    const float &specular_tint, const float &roughness, const float &sheen,
    const float &sheen_tint, const float &ior, const float &transmission,
    const float &transmission_roughness, const float &emission,
    std::vector<std::shared_ptr<Material>> *mats) {
  mats->push_back(std::make_shared<Material>(
      color, metallic, specular, specular_tint, roughness, sheen, sheen_tint,
      ior, transmission, transmission_roughness, emission));
  return LuaMaterial{mats->back()};
}
} // namespace specula

#endif // SPECULA_MATERIAL_MATERIAL_HPP_
