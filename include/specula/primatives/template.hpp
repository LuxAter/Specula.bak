#ifndef SPECULA_PRIMATIVES_TEM_HPP_
#define SPECULA_PRIMATIVES_TEM_HPP_

#include "primative.hpp"

#include <functional>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "../log.hpp"

namespace specula {
class tem : public Primative {
public:
  tem();
};

inline LuaPrimative Luatem(,
                              std::vector<std::shared_ptr<Primative>> *objs) {
  objs->push_back(std::make_shared<tem>(r));
  return LuaPrimative{objs->back()};
}
} // namespace specula

#endif // SPECULA_PRIMATIVES_TEM_HPP_
