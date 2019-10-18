#define GLM_FORCE_SWIZZLE
#include "specula/primatives/cylinder_infinite.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::InfiniteCylinder::InfiniteCylinder(const float &r)
    : Primative([this](const glm::vec3 &p) {
        return glm::length(p.xz()) - this->radius_;
      }),
      radius_(r) {
}
