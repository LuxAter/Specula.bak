#ifndef SPECULA_PRIMATIVES_TRIANGLE_HPP_
#define SPECULA_PRIMATIVES_TRIANGLE_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Triangle : public Primative {
public:
  Triangle(const float &x1, const float &y1, const float &z1, const float &x2,
           const float &y2, const float &z2, const float &x3, const float &y3,
           const float &z3);
  glm::vec3 a_, b_, c_;
};

inline LuaPrimative
LuaTriangle(const float &x1, const float &y1, const float &z1, const float &x2,
            const float &y2, const float &z2, const float &x3, const float &y3,
            const float &z3, std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(
      std::make_shared<Triangle>(x1, y1, z1, x2, y2, z2, x3, y3, z3));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_TRIANGLE_HPP_
