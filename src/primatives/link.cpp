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
  this->source_ =
      fmt::format("float3 q = (float3)(p.x, "
                  "max(abs(p.y)-{{%1$s-link.len}},0.0),p.z); return "
                  "length((float2)(length(q.xy)-{{%1$s-link.router}},q.z))-{{%"
                  "1$s-link.rinner}}",
                  this->id_.c_str());
  this->params_[fmt::format("%s-link.len", this->id_.c_str())] = &length_;
  this->params_[fmt::format("%s-link.router", this->id_.c_str())] = &router_;
  this->params_[fmt::format("%s-link.rinner", this->id_.c_str())] = &rinner_;
}
