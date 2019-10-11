#ifndef SPECULA_PRIMATIVES_PRISM_TRIANGULAR_HPP_
#define SPECULA_PRIMATIVES_PRISM_TRIANGULAR_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class TriangularPrism : public Primative {
public:
  TriangularPrism(const float &a, const float &b);
};

inline LuaPrimative
LuaTriangularPrism(const float &a, const float &b,
                   std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<TriangularPrism>(a, b));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_PRISM_TRIANGULAR_HPP_
