#include "shader/shader.hpp"

#include <memory>

#include <glm/glm.hpp>

#include "material/material.hpp"
#include "rand.hpp"
#include "ray.hpp"

std::tuple<glm::vec3, glm::vec3>
specula::shader::make_ortho_coord_sys(const glm::vec3 &v1) {
  glm::vec3 v2, v3;
  if (glm::abs(v1.x) > glm::abs(v1.y))
    v2 = glm::vec3(-v1.z, 0.0f, v1.x) *
         (1.0f / glm::sqrt(v1.x * v1.x + v1.z * v1.z));
  else
    v2 = glm::vec3(0.0f, v1.z, -v1.y) *
         (1.0f / glm::sqrt(v1.y * v1.y + v1.z * v1.z));
  v3 = glm::cross(v1, v2);
  return std::make_tuple(v2, v3);
}

specula::ray specula::shader::sample_bsdf(
    const glm::vec4 &p, const ray &out, const glm::vec3 &normal,
    const std::shared_ptr<material::Material> &mat, const float &ep) {
  switch (mat->type) {
  case material::Type::DIFFUSE: {
    auto [rotx, roty] = make_ortho_coord_sys(normal);
    const float u1 = rand::frand(), u2 = rand::frand();
    const float r = glm::sqrt(1.0f - u1 * u1);
    const float phi = 2.0f * M_PI * u2;
    glm::vec3 sampled_dir(glm::cos(phi) * r, glm::sin(phi) * r, u1);
    glm::vec3 dir(glm::dot(glm::vec3(rotx.x, roty.x, normal.x), sampled_dir),
                  glm::dot(glm::vec3(rotx.y, roty.y, normal.y), sampled_dir),
                  glm::dot(glm::vec3(rotx.z, roty.z, normal.z), sampled_dir));
    return {p + (2.0f * ep * normal), dir};
  }
  case material::Type::SPECULAR: {
    glm::vec3 dir = glm::reflect(out.d, normal);
    return {p + (2.0f * ep * normal), dir};
  }
  case material::Type::REFRACTIVE: {
    glm::vec3 dir = glm::refract(out.d, normal, mat->ior);
    return {p + (2.0f * ep * normal), dir};
  }
  default:
    return {p + (2.0f * ep * normal), {0.0f, 0.0f, 0.0f}};
  };
}

glm::vec3
specula::shader::evaluate(const glm::vec4 &p, const ray &out,
                          const ray &incident, const glm::vec3 &normal,
                          const glm::vec3 &incoming,
                          const std::shared_ptr<material::Material> &mat) {
  switch (mat->type) {
  case material::Type::DIFFUSE:
    return 2.0f * incoming * mat->base_color * glm::dot(incident.d, normal);
  case material::Type::SPECULAR:
    return incoming;
  case material::Type::REFRACTIVE:
    return incoming * 1.15f;
  default:
    return {0.0f, 0.0f, 0.0f};
  };
}
