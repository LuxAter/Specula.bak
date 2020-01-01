#include <specula/shader/material.hpp>

#include <glm/glm.hpp>

#include "specula/rand.hpp"

specula::Material::Material()
    : base_color(0.0f), transmittance_color(0.0f), emission_color(0.0f),
      sheen(0.0f), sheen_tint(0.0f), clearcoat(0.0f), clearcoat_gloss(0.0f),
      metallic(0.0f), spec_trans(0.0f), diff_trans(0.0f), flatness(0.0f),
      anisotropic(0.0f), ior(0.0f), specular_tint(0.0f), roughness(0.0f),
      scatter_distance(0.0f), uuid(ulrand()) {}