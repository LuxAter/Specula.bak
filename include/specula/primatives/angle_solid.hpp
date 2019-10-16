#ifndef SPECULA_PRIMATIVES_ANGLE_SOLID_HPP_
#define SPECULA_PRIMATIVES_ANGLE_SOLID_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class SolidAngle : public Primative {
public:
  SolidAngle(const float &a, const float &b, const float &ra);

  glm::vec2 c_;
  float ra_;
};

inline LuaPrimative
LuaSolidAngle(const float &a, const float &b, const float &ra,
              std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<SolidAngle>(a, b, ra));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_ANGLE_SOLID_HPP_
