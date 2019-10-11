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
  Cylinder(const float &x, const float &y, const float &z);
};

inline LuaPrimative LuaCylinder(const float &x, const float &y, const float &z,
                                std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Cylinder>(x, y, z));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CYLINDER_HPP_
