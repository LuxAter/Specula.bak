#ifndef SPECULA_PRIMATIVES_CAPSULE_VERTICAL_HPP_
#define SPECULA_PRIMATIVES_CAPSULE_VERTICAL_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class VerticalCapsule : public Primative {
public:
  VerticalCapsule(const float &h, const float &r);
   float height_, radius_;
};

inline LuaPrimative
LuaVerticalCapsule(const float &h, const float &r,
                   std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<VerticalCapsule>(h, r));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CAPSULE_VERTICAL_HPP_
