#ifndef SPECULA_PRIMATIVES_OCTAHEDRON_HPP_
#define SPECULA_PRIMATIVES_OCTAHEDRON_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Octahedron : public Primative {
public:
  Octahedron(const float &r);
};

inline LuaPrimative
LuaOctahedron(const float &r, std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Octahedron>(r));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_OCTAHEDRON_HPP_
