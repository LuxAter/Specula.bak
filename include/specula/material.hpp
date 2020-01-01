#ifndef MATERIAL_HPP_JUHQL8EO
#define MATERIAL_HPP_JUHQL8EO

#include <glm/glm.hpp>

namespace specula
{
  struct Material {
    enum MicrofacetDist {
      GGX, MultipleScatteringGGX
    };
    MicrofacetDist distribution;
    glm::vec3 base_color;
    float subsurface;
    glm::vec3 subsurface_radius;
    glm::vec3 subsurface_color;
    float metallic;
    float specular;
    float specular_tint;
    float roughness;
    float anisotropic;
    float anisotropic_rotation;
    float sheen;
    float sheen_tint;
    float clearcoat;
    float clearcoat_roughness;
    float ior;
    float transmission;
  };
} /* specula */ 

#endif /* end of include guard: MATERIAL_HPP_JUHQL8EO */
