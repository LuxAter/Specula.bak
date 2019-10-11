#ifndef SPECULA_PRIMATIVES_TORUS_HPP_
#define SPECULA_PRIMATIVES_TORUS_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Torus : public Primative {
public:
  Torus(const float &r_big, const float &r_small);

  glm::vec2 torus_;
};

inline LuaPrimative LuaTorus(const float &r_big, const float &r_small,
                             std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Torus>(r_big, r_small));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_TORUS_HPP_
