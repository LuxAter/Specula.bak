#ifndef SPECULA_PRIMATIVES_CYLINDER_HPP_
#define SPECULA_PRIMATIVES_CYLINDER_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Cylinder : public Primative {
public:
  Cylinder(const float &r);

  float radius_;
};

inline LuaPrimative LuaCylinder(const float &r,
                                std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Cylinder>(r));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CYLINDER_HPP_
