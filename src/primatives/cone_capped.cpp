#define GLM_FORCE_SWIZZLE
#include "specula/primatives/cone_capped.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::CappedCone::CappedCone(const float &h, const float &r1,
                                const float &r2)
    : Primative([this](const glm::vec3 &p) {
        glm::vec2 q(glm::length(p.xz()), p.y);
        glm::vec2 k1(this->r2_, this->height_);
        glm::vec2 k2(this->r2_ - this->r1_, 2.0f * this->height_);
        glm::vec2 ca(q.x - glm::min(q.x, (q.y < 0.0) ? this->r1_ : this->r2_),
                     glm::abs(q.y) - this->height_);
        glm::vec2 cb = q - k1 +
                       k2 * glm::clamp(glm::dot(k1 - q, k2) / glm::dot(k2, k2),
                                       0.0f, 1.0f);
        float s = (cb.x < 0.0 && ca.y < 0.0) ? -1.0 : 1.0;
        return s * glm::sqrt(glm::min(glm::dot(ca, ca), glm::dot(cb, cb)));
      }),
      height_(h), r1_(r1), r2_(r2) {
  this->source_ = fmt::format(
      "float2 q(length(p.xz), p.y); float2 "
      "k1({{%1$s-capped-cone.r2}},{%1$s-capped-cone.height}); float2 "
      "k2({{%1$s-capped-cone.r2}}-{{%1$s-capped-cone.r1}},2.0*{{%1$s-capped-"
      "cone.height}}); float2 "
      "ca(q.x-min(q.x,(q.y<0.0)?{{%1$s-capped-cone.r1}}:{{%1$s-capped-cone.r2}}"
      "), abs(q.y)-h); float2 cb = "
      "q-k1+k2*clamp(dot(k1-q,k2)/dot(k2,k2),0.0,1.0); float s = (cb.x < 0.0 "
      "&& ca.y < 0.0) ? -1.0 : 1.0; return s*sqrt(min(dot(ca,ca),dot(cb,cb)));",
      this->id_.c_str());
  this->params_[fmt::format("%s-capped-cone.r1", this->id_.c_str())] = &r1_;
  this->params_[fmt::format("%s-capped-cone.r2", this->id_.c_str())] = &r2_;
  this->params_[fmt::format("%s-capped-cone.height", this->id_.c_str())] =
      &height_;
}
