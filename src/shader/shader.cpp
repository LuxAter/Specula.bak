#include "shader/shader.hpp"

#include <memory>

#include "math.hpp"
#include "rand.hpp"
#include "shader/material.hpp"

glm::vec3 specula::sample_bsdf(const std::shared_ptr<Material> &medium,
                               const std::shared_ptr<Material> &mat,
                               const glm::vec3 &lo, const glm::vec3 &n) {
  switch (mat->type) {
  case Material::DIFFUSE: {
    auto [rotx, roty] = make_ortho_coord_sys(n);
    const float u1 = frand(), u2 = frand();
    const float r = std::sqrt(1.0 - u1 * u1);
    const float phi = 2.0f * M_PI * u2;
    glm::vec3 sampled_dir(std::cos(phi) * r, std::sin(phi) * r, u1);
    return glm::vec3(glm::dot(glm::vec3(rotx.x, roty.x, n.x), sampled_dir),
                     glm::dot(glm::vec3(rotx.y, roty.y, n.y), sampled_dir),
                     glm::dot(glm::vec3(rotx.z, roty.z, n.z), sampled_dir));
  }
  case Material::SPECULAR: {
    return glm::reflect(lo, n);
  }
  case Material::TRANSPARENT: {
    return glm::refract(lo, n,
                        medium != nullptr ? (medium->ior / mat->ior)
                                          : (1.0f / mat->ior));
  }
  case Material::EMISSIVE: {
    return glm::vec3(0.0f);
  }
  default:
    return glm::vec3(0.0f);
  };
}
glm::vec3 specula::evaluate_bsdf(const std::shared_ptr<Material> &mat,
                                 const glm::vec3 &ri, const glm::vec3 &li,
                                 const glm::vec3 &lo, const glm::vec3 &n) {
  switch (mat->type) {
  case Material::DIFFUSE: {
    return mat->emission * mat->base_color +
           2.0f * ri * mat->base_color * glm::dot(li, n);
  }
  case Material::SPECULAR: {
    return mat->emission * mat->base_color + ri;
  }
  case Material::TRANSPARENT: {
    return mat->emission * mat->base_color + 1.15f * ri;
  }
  case Material::EMISSIVE: {
    return mat->emission * mat->base_color;
  }
  default:
    return glm::vec3(0.0f);
  };
}
