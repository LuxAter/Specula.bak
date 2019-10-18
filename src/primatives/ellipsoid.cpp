#include "specula/primatives/ellipsoid.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::Ellipsoid::Ellipsoid(const float &rx, const float &ry, const float &rz)
    : Primative([this](const glm::vec3 &p) {
        float k0 = glm::length(p / this->radius_);
        float k1 = glm::length(p / (this->radius_ * this->radius_));
        return k0 * (k0 - 1.0f) / k1;
      }),
      radius_(rx, ry, rz) {}
