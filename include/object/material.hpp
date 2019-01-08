#ifndef SPECULA_OBJECT_MATERIAL_HPP_
#define SPECULA_OBJECT_MATERIAL_HPP_

#include "../color.hpp"

namespace specula {
namespace object {
  class Material {
   public:
    enum DiffuseShader { LAMBERT_DIFFUSE, BURLEY_DIFFUSE };
    enum SpecularShader { PHONG_SPECULAR, BLINN_SPECULAR, COOK_TORR_SPECULAR };

    Material()
        : base_color(1.0),
          specular_color(1.0),
          diffuse_shader(LAMBERT_DIFFUSE),
          specular_shader(PHONG_SPECULAR),
          ka(0.2),
          kd(0.5),
          ks(0.3),
          hardness(50.0),
          ior(4.0) {}

    Color base_color;
    Color specular_color;

    DiffuseShader diffuse_shader;
    SpecularShader specular_shader;

    double ka, kd, ks;
    double hardness;
    double ior;
  };
}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_MATERIAL_HPP_
