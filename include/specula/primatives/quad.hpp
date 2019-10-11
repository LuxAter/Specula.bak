#ifndef SPECULA_PRIMATIVES_QUAD_HPP_
#define SPECULA_PRIMATIVES_QUAD_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Quad : public Primative {
public:
  Quad(const float &x1, const float &y1, const float &z1, const float &x2,
       const float &y2, const float &z2, const float &x3, const float &y3,
       const float &z3, const float &x4, const float &y4, const float &z4);
};

inline LuaPrimative LuaQuad(const float &x1, const float &y1, const float &z1,
                            const float &x2, const float &y2, const float &z2,
                            const float &x3, const float &y3, const float &z3,
                            const float &x4, const float &y4, const float &z4,
                            std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(
      std::make_shared<Quad>(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_QUAD_HPP_
