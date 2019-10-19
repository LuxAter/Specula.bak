#ifndef SPECULA_PRIMATIVES_DERIVED_HPP_
#define SPECULA_PRIMATIVES_DERIVED_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class DerivedPrimative : public Primative {
public:
  enum DeriviedTypes {
    UNION,
    SUBTRACTION,
    INTERSECTION,
    SMOOTH_UNION,
    SMOOTH_SUBTRACTION,
    SMOOTH_INTERSECTION
  };
  DerivedPrimative(const std::shared_ptr<Primative> &a,
                   const std::shared_ptr<Primative> &b,
                   const DeriviedTypes &type, float r = 0.0);

  std::shared_ptr<Primative> a_, b_;
  float radius_;
};

inline LuaPrimative LuaUnion(const LuaPrimative &lhs, const LuaPrimative &rhs,
                             std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<DerivedPrimative>(
      lhs.base_, rhs.base_, DerivedPrimative::DeriviedTypes::UNION));
  return LuaPrimative{objs->back()};
}
inline LuaPrimative
LuaSubtraction(const LuaPrimative &lhs, const LuaPrimative &rhs,
               std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<DerivedPrimative>(
      lhs.base_, rhs.base_, DerivedPrimative::DeriviedTypes::SUBTRACTION));
  return LuaPrimative{objs->back()};
}
inline LuaPrimative
LuaIntersection(const LuaPrimative &lhs, const LuaPrimative &rhs,
                std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<DerivedPrimative>(
      lhs.base_, rhs.base_, DerivedPrimative::DeriviedTypes::INTERSECTION));
  return LuaPrimative{objs->back()};
}
inline LuaPrimative
LuaSmoothUnion(const LuaPrimative &lhs, const LuaPrimative &rhs,
               std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<DerivedPrimative>(
      lhs.base_, rhs.base_, DerivedPrimative::DeriviedTypes::SMOOTH_UNION));
  return LuaPrimative{objs->back()};
}
inline LuaPrimative
LuaSmoothSubtraction(const LuaPrimative &lhs, const LuaPrimative &rhs,
                     std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<DerivedPrimative>(
      lhs.base_, rhs.base_,
      DerivedPrimative::DeriviedTypes::SMOOTH_SUBTRACTION));
  return LuaPrimative{objs->back()};
}
inline LuaPrimative
LuaSmoothIntersection(const LuaPrimative &lhs, const LuaPrimative &rhs,
                      std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<DerivedPrimative>(
      lhs.base_, rhs.base_,
      DerivedPrimative::DeriviedTypes::SMOOTH_INTERSECTION));
  return LuaPrimative{objs->back()};
}

} // namespace specula

#endif // SPECULA_PRIMATIVES_ROUNDED_HPP_
