#ifndef SPECULA_PRIMATIVES_CYLINDER_CAPPED_HPP_
#define SPECULA_PRIMATIVES_CYLINDER_CAPPED_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class CappedCylinder : public Primative {
public:
  CappedCylinder(const float &h, const float &r);

  float height_, radius_;
};

inline LuaPrimative
LuaCappedCylinder(const float &h, const float &r,
                  std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<CappedCylinder>(h, r));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CYLINDER_CAPPED_HPP_
