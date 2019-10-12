#ifndef SPECULA_PRIMATIVES_PRISM_HEXAGONAL_HPP_
#define SPECULA_PRIMATIVES_PRISM_HEXAGONAL_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class HexagonalPrism : public Primative {
public:
  HexagonalPrism(const float &a, const float &b);
  float a_, b_;
};

inline LuaPrimative
LuaHexagonalPrism(const float &a, const float &b,
                  std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<HexagonalPrism>(a, b));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_PRISM_HEXAGONAL_HPP_
