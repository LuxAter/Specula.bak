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
  Cone(const float &alpha);

  glm::vec2 cone_;
};

inline LuaPrimative LuaCone(const float &alpha,
                            std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Cone>(alpha));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CONE_HPP_
