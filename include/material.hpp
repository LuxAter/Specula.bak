#ifndef SPECULA_MATERIAL_HPP_
#define SPECULA_MATERIAL_HPP_

#include <string>

#include "color.hpp"

namespace specula {
struct Material {
 public:
  Material();
  Material(std::string n, Color am, Color di, Color sp, double se, double tr,
           double od, int sh = 60);

  std::string name;
  double specular_exp;
  double transparency, optical_density;
  int illum, sharpness;
  Color ambient, diffuse, specular;

  double emisivity;
  Color emmisive;

 private:
};
}  // namespace specula

#endif  // SPECULA_MATERIAL_HPP_
