#ifndef SPECULA_PRIMATIVES_BOX_ROUND_HPP_
#define SPECULA_PRIMATIVES_BOX_ROUND_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class RoundBox : public Primative {
public:
  RoundBox(const float &w, const float &l, const float &h, const float &r);

  glm::vec3 box_;
  float radius_;
};

inline LuaPrimative LuaRoundBox(const float &w, const float &l, const float &h,
                                const float &r,
                                std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<RoundBox>(w, l, h, r));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_BOX_ROUND_HPP_
