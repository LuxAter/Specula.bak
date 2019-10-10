#ifndef SPECULA_PRIMATIVES_SPHERE_HPP_
#define SPECULA_PRIMATIVES_SPHERE_HPP_

#include "primative.hpp"

#include <functional>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Sphere : public Primative {
public:
  Sphere(const float &r);

  float radius_;
};

inline LuaPrimative LuaSphere(const float &r,
                              std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Sphere>(r));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_SPHERE_HPP_
