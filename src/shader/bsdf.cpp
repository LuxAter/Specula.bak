#include "specula/shader/bsdf.hpp"

#include <memory>

#include <glm/glm.hpp>

#include "specula/shader/material.hpp"

glm::vec3 specula::shader::sample_bsdf(const std::shared_ptr<Material> &medium,
                                       const std::shared_ptr<Material> &mat,
                                       const glm::vec3 &dir,
                                       const glm::vec3 &normal) {
  return glm::vec3(0.0f);
}