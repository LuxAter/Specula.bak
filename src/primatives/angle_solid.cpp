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
      c_(a, b), ra_(ra) {
  this->source_ = fmt::format(
      "float2 q = (float2)(length(p.xz), p.y); float l = length(q) - "
      "{{%1$s-solid-angle.ra}}; float m = "
      "length(q-{{%1$s-solid-angle.c}}*clamp(dot(q,{{%1$s-solid-angle.c}}),0.0f,"
      "{{%1$s-solid-angle.ra}})); return "
      "max(l,m*sign({{%1$s-solid-angle.b}}*q.x-{{%1$s-solid-angle.a}}*q.y));",
      this->id_.c_str());
  this->params_[fmt::format("%s-solid-angle.c", this->id_.c_str())] = &c_;
  this->params_[fmt::format("%s-solid-angle.a", this->id_.c_str())] = &c_.x;
  this->params_[fmt::format("%s-solid-angle.b", this->id_.c_str())] = &c_.y;
  this->params_[fmt::format("%s-solid-angle.ra", this->id_.c_str())] = &ra_;
}
