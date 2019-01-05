#ifndef SPECULA_OBJECT_MATERIAL_HPP_
#define SPECULA_OBJECT_MATERIAL_HPP_

#include "../color.hpp"

namespace specula {
namespace object {
  class Material {
   public:
     Color base_color;
     double ks, kd, ka;
     double alpha;
     double roughness;
     double metallic;
     double specular;
  };
}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_MATERIAL_HPP_
