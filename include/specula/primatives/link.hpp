#ifndef SPECULA_PRIMATIVES_LINK_HPP_
#define SPECULA_PRIMATIVES_LINK_HPP_

#include "primative.hpp"

#include <functional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class Link : public Primative {
public:
  Link(const float &len, const float &r_outer, const float &r_inner);
};

inline LuaPrimative LuaLink(const float &len, const float &r_outer,
                            const float &r_inner,
                            std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<Link>(len, r_outer, r_inner));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_LINK_HPP_
