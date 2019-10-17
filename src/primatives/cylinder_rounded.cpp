#define GLM_FORCE_SWIZZLE
#include "specula/primatives/cylinder_rounded.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::RoundedCylinder::RoundedCylinder(const float &ra, const float &rb,
                                          const float &h)
    : Primative([this](const glm::vec3 &p) {
        glm::vec2 d(glm::length(p.xz()) - 2.0 * this->ra_ + this->rb_,
                    glm::abs(p.y) - this->height_);
        return glm::min(glm::max(d.x, d.y), 0.0f) +
               glm::length(glm::max(d, 0.0f)) - this->rb_;
      }),
      ra_(ra), rb_(rb), height_(h) {
  this->source_ = fmt::format(
      "float2 d = (float2)(length(p.xz) - 2.0f * {{%1$s-rounded-cylinder.ra}} + "
      "{{%1$s-rounded-cylinder.rb}}, fabs(p.y) - "
      "{{%1$s-rounded-cylinder.height}}); return min(max(d.x,d.y), 0.0f) + "
      "length(max(d,0.0f)) - {{%1$s-rounded-cylinder.rb}};",
      this->id_.c_str());
  this->params_[fmt::format("%s-rounded-cylinder.height", this->id_.c_str())] =
      &height_;
  this->params_[fmt::format("%s-rounded-cylinder.ra", this->id_.c_str())] =
      &ra_;
  this->params_[fmt::format("%s-rounded-cylinder.rb", this->id_.c_str())] =
      &rb_;
}
