#ifndef SPECULA_PRIMATIVES_BOX_HPP_
#define SPECULA_PRIMATIVES_BOX_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Box : public Primative {
public:
  Box(const float &w, const float &l, const float &h);

  glm::vec3 box_;
};

inline LuaPrimative LuaBox(const float &w, const float &l, const float &h,
                           std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Box>(w, l, h));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_BOX_HPP_
