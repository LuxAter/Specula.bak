#ifndef SPECULA_PRIMATIVES_CYLINDER_ROUNDED_HPP_
#define SPECULA_PRIMATIVES_CYLINDER_ROUNDED_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class RoundedCylinder : public Primative {
public:
  RoundedCylinder(const float &ra, const float &rb, const float &h);
  float ra_, rb_, height_;
};

inline LuaPrimative
LuaRoundedCylinder(const float &ra, const float &rb, const float &h,
                   std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<RoundedCylinder>(ra, rb, h));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CYLINDER_ROUNDED_HPP_
