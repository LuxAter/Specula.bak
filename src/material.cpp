#include "material.hpp"

#include <string>

#include "color.hpp"

specula::Material::Material()
    : specular_exp(60),
      transparency(0.0),
      optical_density(1.0),
      sharpness(60),
      ambient({1.0, 1.0, 1.0}),
      diffuse({1.0, 1.0, 1.0}),
      specular({1.0, 1.0, 1.0}),
      emisivity(0),
      emmisive({1.0, 1.0, 1.0}) {}

specula::Material::Material(std::string n, Color am, Color di, Color sp,
                            double se, double tr, double od, int sh)
    : specular_exp(se),
      transparency(tr),
      optical_density(od),
      sharpness(sh),
      ambient(am),
      diffuse(di),
      specular(sp) {}
