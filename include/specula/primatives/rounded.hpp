#ifndef SPECULA_PRIMATIVES_ROUNDED_HPP_
#define SPECULA_PRIMATIVES_ROUNDED_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class RoundedPrimative : public Primative {
public:
  RoundedPrimative(const std::shared_ptr<Primative> &base, const float &r);

  float radius_;
  std::shared_ptr<Primative> base_;
};

inline LuaPrimative LuaRound(const LuaPrimative &base, const float &r,
                             std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<RoundedPrimative>(base->base_, r));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_ROUNDED_HPP_
