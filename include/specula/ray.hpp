#ifndef SPECULA_RAY_HPP_
#define SPECULA_RAY_HPP_

#include <glm/glm.hpp>

#include "shader/material.hpp"

namespace specula {
struct Ray {
  glm::vec3 o;
  glm::vec3 d;
  std::shared_ptr<Material> medium;
};
} // namespace specula

#endif // !SPECULA_RAY_HPP_