#ifndef SPECULA_PRIMATIVES_CONE_CAPPED_HPP_
#define SPECULA_PRIMATIVES_CONE_CAPPED_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class CappedCone : public Primative {
public:
  CappedCone(const float &h, const float &r1, const float &r2);
};

inline LuaPrimative
LuaCappedCone(const float &h, const float &r1, const float &r2,
              std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<CappedCone>(h, r1, r2));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CONE_CAPPED_HPP_
