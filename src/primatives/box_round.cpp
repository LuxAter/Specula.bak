#include "specula/primatives/box_round.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::RoundBox::RoundBox(const float &w, const float &l, const float &h,
                            const float &r)
    : Primative([this](const glm::vec3 &p) {
        glm::vec3 d = glm::abs(p) - this->box_;
        return glm::length(glm::max(d, 0.0f)) - this->radius_ +
               glm::min(glm::max(d.x, glm::max(d.y, d.z)), 0.0f);
      }),
      box_(w, l, h), radius_(r) {
}
