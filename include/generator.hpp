#ifndef SPECULA_GENERATOR_HPP_
#define SPECULA_GENERATOR_HPP_

#include <map>
#include <string>

#include "math.hpp"
#include "variant.hpp"

namespace specula {
std::string format(
    std::string fmt,
    const std::map<std::string, variant<float, glm::vec2, glm::vec3, glm::vec4>>
        &variables);
} // namespace specula

#endif // SPECULA_GENERATOR_HPP_
