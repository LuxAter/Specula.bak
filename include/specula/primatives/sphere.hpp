#ifndef SPECULA_PRIMATIVES_SPHERE_HPP_
#define SPECULA_PRIMATIVES_SPHERE_HPP_

#include "primative.hpp"

#include <array>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Sphere : public Primative {
public:
  Sphere(const float &r);
  Sphere(const float &r, const std::array<double, 3> &c);
  Sphere(const float &r, const glm::vec3 &p, const std::array<double, 3> &c);

  float intersect(const glm::vec3 &o, const glm::vec3 &d) const;
  float radius_;
};

inline LuaPrimative LuaSphere(const float &r,
                              std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(
      std::make_shared<Sphere>(r, std::array<double, 3>{0.0, 1.0, 0.0}));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_SPHERE_HPP_
