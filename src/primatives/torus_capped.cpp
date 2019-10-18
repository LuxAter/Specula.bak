#define GLM_FORCE_SWIZZLE
#include "specula/primatives/torus_capped.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::CappedTorus::CappedTorus(const float &r_big, const float &r_small,
                                  const float &ra, const float &rb)
    : Primative([this](const glm::vec3 &p) {
        glm::vec3 pt(glm::abs(p.x), p.y, p.z);
        float k = (this->torus_.y * pt.x > this->torus_.x * pt.y)
                      ? glm::dot(pt.xy(), this->torus_)
                      : glm::length(pt.xy());
        return glm::sqrt(glm::dot(pt, pt) + this->ra_ * this->ra_ -
                         2.0 * this->ra_ * k) -
               this->rb_;
      }),
      torus_(r_big, r_small), ra_(ra), rb_(rb) {}
