#ifndef SPECULA_PRIMATIVES_CONE_ROUND_HPP_
#define SPECULA_PRIMATIVES_CONE_ROUND_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class RoundCone : public Primative {
public:
  RoundCone(const float &r1, const float &r2, const float &h);
  float height_, r1_, r2_;
};

inline LuaPrimative
LuaRoundCone(const float &r1, const float &r2, const float &h,
             std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<RoundCone>(r1, r2, h));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CONE_ROUND_HPP_
