#ifndef SPECULA_PRIMATIVES_CONE_INFINITE_HPP_
#define SPECULA_PRIMATIVES_CONE_INFINITE_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class InfiniteCone : public Primative {
public:
  InfiniteCone(const float &alpha);

  glm::vec2 cone_;
};

inline LuaPrimative LuaInfiniteCone(const float &alpha,
                                    std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<InfiniteCone>(alpha));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_CONE_INFINITE_HPP_
