#ifndef SPECULA_PRIMATIVES_CYLINDER_INFINITE_HPP_
#define SPECULA_PRIMATIVES_CYLINDER_INFINITE_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class InfiniteCylinder : public Primative {
public:
  InfiniteCylinder(const float &r);

  float radius_;
};

inline LuaPrimative LuaInfiniteCylinder(const float &r,
                                        std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<InfiniteCylinder>(r));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CYLINDER_INFINITE_HPP_
