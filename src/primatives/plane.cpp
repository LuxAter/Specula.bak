#define GLM_FORCE_SWIZZLE
#include "specula/primatives/plane.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::Plane::Plane(const float &x, const float &y, const float &z,
                      const float &w)
    : Primative([this](const glm::vec3 &p) {
        return glm::dot(p, this->normal_.xyz()) + this->normal_.w;
      }),
      normal_(glm::normalize(glm::vec4(x, y, z, w))) {
}
