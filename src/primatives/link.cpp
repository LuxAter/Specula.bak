#define GLM_FORCE_SWIZZLE
#include "specula/primatives/link.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::Link::Link(const float &len, const float &r_outer,
                    const float &r_inner)
    : Primative([this](const glm::vec3 &p) {
        glm::vec3 q(p.x, glm::max(glm::abs(p.y) - this->length_, 0.0f), p.z);
        return glm::length(glm::vec2(glm::length(q.xy()) - this->router_, q.z)) -
               this->rinner_;
      }),
      length_(len), router_(r_outer), rinner_(r_inner) {
}
