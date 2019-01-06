#ifndef SPECULA_OBJECT_MATERIAL_HPP_
#define SPECULA_OBJECT_MATERIAL_HPP_

#include "../color.hpp"

namespace specula {
namespace object {
  class Material {
   public:
     Material(): base_color(0.0), specular_color(0.0), ai(0.2), di(0.5), si(0.3){}
     Material(Color bc): base_color(bc), specular_color(bc){}
     Color base_color, specular_color;
     double ai, di, si;
     double alpha;
     double roughness;
     double metallic;
     double specular;
  };
}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_MATERIAL_HPP_
