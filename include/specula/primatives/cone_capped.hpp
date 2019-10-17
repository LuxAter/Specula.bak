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
  Cone(const float &h, const float &r1, const float &r2);

  float height_, r1_, r2_;
};

inline LuaPrimative
LuaCone(const float &h, const float &r1, const float &r2,
        std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Cone>(h, r1, r2));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CONE_PP_
