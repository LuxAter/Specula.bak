#ifndef SPECULA_PRIMATIVES_HPP_
#define SPECULA_PRIMATIVES_HPP_

#include <memory>

#include <glm/glm.hpp>

#include "object.hpp"

namespace specula {
std::shared_ptr<Object> Sphere(const float &radius);
std::shared_ptr<Object> Box(const glm::vec3& dims);
} // namespace specula

#endif // SPECULA_PRIMATIVES_HPP_
