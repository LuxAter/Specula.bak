#define GLM_FORCE_SWIZZLE
#include "specula/primatives/cylinder_capped.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::CappedCylinder::CappedCylinder(const float &h, const float &r)
    : Primative([this](const glm::vec3 &p) {
        glm::vec2 d = glm::abs(glm::vec2(glm::length(p.xz()), p.y)) -
                      glm::vec2(this->height_, this->radius_);
        return glm::min(glm::max(d.x, d.y), 0.0f) +
               glm::length(glm::max(d, 0.0f));
      }),
      height_(h), radius_(r) {
  this->source_ = fmt::format(
      "float2 d = abs((float2)(length(p.xz), p.y)) - "
      "(float2)({{%1$s-capped-cylinder.height}},{{%1$s-capped-cylinder.radius}}"
      "); return min(max(d.x,d.y),0.0) + length(max(d,0.0));",
      this->id_.c_str());
  this->params_[fmt::format("%s-capped-cylinder.height", this->id_.c_str())] =
      &height_;
  this->params_[fmt::format("%s-capped-cylinder.radius", this->id_.c_str())] =
      &radius_;
}
