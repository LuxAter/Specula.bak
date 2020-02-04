#ifndef SPECULA_VARIABLE_HPP_
#define SPECULA_VARIABLE_HPP_

#include <iostream>

#include <glm/glm.hpp>

#include "extern/variant.hpp"

namespace specula {
typedef variant<bool, glm::bvec2, glm::bvec3, glm::bvec4, int, glm::ivec2,
                glm::ivec3, glm::ivec4, float, glm::vec2, glm::vec3, glm::vec4>
    Variable;
} // namespace specula

#endif // SPECULA_VARIABLE_HPP_
