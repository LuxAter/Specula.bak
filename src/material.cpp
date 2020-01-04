#include "specula/material.hpp"

#include <memory>

#include <glm/glm.hpp>

std::shared_ptr<specula::Material> specula::Diffuse(const glm::vec3 &color) {
  return std::make_shared<Material>()->set_base_color(color);
}