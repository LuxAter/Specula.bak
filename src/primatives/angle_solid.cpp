#define GLM_FORCE_SWIZZLE
#include "specula/primatives/angle_solid.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::SolidAngle::SolidAngle(const float &a, const float &b, const float &ra)
    : Primative([this](const glm::vec3 &p) {
        glm::vec2 q(glm::length(p.xz()), p.y);
        float l = glm::length(q) - this->ra_;
        float m = glm::length(
            q - this->c_ * glm::clamp(glm::dot(q, this->c_), 0.0f, this->ra_));
        return glm::max(l, m * glm::sign(this->c_.y * q.x - this->c_.x * q.y));
      }),
      c_(a, b), ra_(ra) {}
