#include "specula/geometry/ray.hpp"

#include <limits>

#include <glm/glm.hpp>

specula::ray::ray() : o(0.0), d(0.0), medium(nullptr) {}

specula::ray::ray(const glm::vec3 &origin, const glm::vec3 &direction,
                  const std::shared_ptr<Material> &mat)
    : o(origin), d(direction), medium(mat) {}
