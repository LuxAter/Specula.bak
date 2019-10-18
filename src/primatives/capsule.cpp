#include "specula/primatives/capsule.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::Capsule::Capsule(const float &x1, const float &y1, const float &z1,
                          const float &x2, const float &y2, const float &z2,
                          const float &r)
    : Primative([this](const glm::vec3 &p) {
        glm::vec3 pa = p - this->a_, ba = this->b_ - this->a_;
        float h = glm::clamp(glm::dot(pa, ba) / glm::dot(ba, ba), 0.0f, 1.0f);
        return glm::length(pa - ba * h) - this->radius_;
      }),
      a_(x1, y1, z1), b_(x2, y2, z2), radius_(r) {
}
