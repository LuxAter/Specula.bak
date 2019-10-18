#include "specula/primatives/capsule_vertical.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::VerticalCapsule::VerticalCapsule(const float &h, const float &r)
    : Primative([this](const glm::vec3 &p) {
        glm::vec3 pt(p.x, p.y - glm::clamp(p.y, 0.0f, this->height_), p.z);
        return length(pt) - this->radius_;
      }),
      height_(h), radius_(r) {
}
