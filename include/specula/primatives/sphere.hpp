#ifndef SPECULA_PRIMATIVES_SPHERE_HPP_
#define SPECULA_PRIMATIVES_SPHERE_HPP_

#include "primative.hpp"

#include <array>

#include <glm/glm.hpp>

namespace specula {
class Sphere : public Primative {
  public:
  Sphere(const float &r, std::array<double, 3>c = {0.0, 0.0, 0.0});
  Sphere(const float &r, const glm::vec3 &p, std::array<double, 3>c = {0.0, 0.0, 0.0});

  float intersect(const glm::vec3 &o, const glm::vec3 &d) const;
  private:
  float radius_;
};
} // namespace specula

#endif // SPECULA_PRIMATIVES_SPHERE_HPP_
