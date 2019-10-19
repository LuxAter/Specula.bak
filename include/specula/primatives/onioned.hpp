#ifndef SPECULA_PRIMATIVES_ONIONED_HPP_
#define SPECULA_PRIMATIVES_ONIONED_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class OnionedPrimative : public Primative {
public:
  OnionedPrimative(const std::shared_ptr<Primative> &base, const float &t);

  float thickness_;
  std::shared_ptr<Primative> base_;
};

inline LuaPrimative LuaOnion(const LuaPrimative &base, const float &t,
                             std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<OnionedPrimative>(base.base_, t));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_ONIONED_HPP_
