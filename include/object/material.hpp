#ifndef SPECULA_OBJECT_MATERIAL_HPP_
#define SPECULA_OBJECT_MATERIAL_HPP_

namespace specula {
namespace object {
  class Material {
   public:
    unsigned ambient;
    unsigned diffuse;
    double diffuse_intensity;
    unsigned specular;
    double specular_intensity, specular_exponent;
  };
}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_MATERIAL_HPP_
