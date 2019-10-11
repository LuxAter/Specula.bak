#ifndef SPECULA_PRIMATIVES_CAPSULE_HPP_
#define SPECULA_PRIMATIVES_CAPSULE_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Capsule : public Primative {
public:
  Capsule(const float &x1, const float &y1, const float &z1, const float &x2,
          const float &y2, const float &z2, const float &r);
};

inline LuaPrimative LuaCapsule(const float &x1, const float &y1,
                               const float &z1, const float &x2,
                               const float &y2, const float &z2, const float &r,
                               std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Capsule>(x1, y1, z1, x2, y2, z1, r));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CAPSULE_HPP_
