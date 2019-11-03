#include "specula/material/bsdf.hpp"

#include <memory>

#include <glm/glm.hpp>

#include "specula/material/material.hpp"

glm::vec3 specula::bsdf::eval(const std::shared_ptr<Material> &mat,
                              const glm::vec3 &l, const glm::vec3 &v,
                              const glm::vec3 &n) {
  glm::vec3 wo = glm::normalize()
}
