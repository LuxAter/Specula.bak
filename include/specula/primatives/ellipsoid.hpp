#ifndef SPECULA_PRIMATIVES_ELLIPSOID_HPP_
#define SPECULA_PRIMATIVES_ELLIPSOID_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Ellipsoid : public Primative {
public:
  Ellipsoid(const float &rx, const float &ry, const float &rz);
  glm::vec3 radius_;
};

inline LuaPrimative
LuaEllipsoid(const float &rx, const float &ry, const float &rz,
             std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Ellipsoid>(rx, ry, rz));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_ELLIPSOID_HPP_
