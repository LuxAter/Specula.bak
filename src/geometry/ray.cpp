#include "specula/geometry/ray.hpp"

#include <limits>

#include <glm/glm.hpp>

specula::ray::ray()
    : o(0.0), d(0.0), t_max(std::numeric_limits<float>::infinity()) {}

specula::ray::ray(const glm::vec3 &origin, const glm::vec3 &direction,
                  float t_max)
    : o(origin), d(direction), t_max(t_max) {}
