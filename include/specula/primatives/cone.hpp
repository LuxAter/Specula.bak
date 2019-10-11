#ifndef SPECULA_PRIMATIVES_CONE_HPP_
#define SPECULA_PRIMATIVES_CONE_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Cone : public Primative {
public:
  Cone(const float &x, const float &y);
};

inline LuaPrimative LuaCone(const float &x, const float &y,
                            std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Cone>(x, y));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CONE_HPP_
