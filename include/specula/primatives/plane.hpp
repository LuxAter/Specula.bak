#ifndef SPECULA_PRIMATIVES_PLANE_HPP_
#define SPECULA_PRIMATIVES_PLANE_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Plane : public Primative {
public:
  Plane(const float &x, const float &y, const float &z, const float &w);

  glm::vec4 normal_;
};

inline LuaPrimative LuaPlane(const float &x, const float &y, const float &z,
                             const float &w,
                             std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Plane>(x, y, z, w));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_PLANE_HPP_
