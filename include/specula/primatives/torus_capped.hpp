#ifndef SPECULA_PRIMATIVES_TORUS_CAPPED_HPP_
#define SPECULA_PRIMATIVES_TORUS_CAPPED_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class CappedTorus : public Primative {
public:
  CappedTorus(const float &r_big, const float &r_small, const float &ra,
              const float &rb);

  glm::vec2 torus_;
  float ra_, rb_;
};

inline LuaPrimative
LuaCappedTorus(const float &r_big, const float &r_small, const float &ra,
               const float &rb, std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<CappedTorus>(r_big, r_small, ra, rb));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_TORUS_HPP_
