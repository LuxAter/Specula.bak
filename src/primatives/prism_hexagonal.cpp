#define GLM_FORCE_SWIZZLE
#include "specula/primatives/prism_hexagonal.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::HexagonalPrism::HexagonalPrism(const float &a, const float &b)
    : Primative([this](const glm::vec3 &p) {
        const glm::vec3 k(-0.8660254, 0.5, 0.57735);
        glm::vec3 pt = glm::abs(p);
        float s = 2.0f * glm::min(glm::dot(k.xy(), pt.xy()), 0.0f);
        pt = glm::vec3(pt.x - s*k.x, pt.y-s*k.y, pt.z);
        glm::vec2 d(
            glm::length(pt.xy() - glm::vec2(glm::clamp(pt.x, -k.z * this->a_,
                                                       k.z * this->a_),
                                            this->a_)) *
                glm::sign(pt.y - this->a_),
            pt.z - this->b_);
        return glm::min(glm::max(d.x, d.y), 0.0f) +
               glm::length(glm::max(d, 0.0f));
      }),
      a_(a), b_(b) {
  this->source_ = fmt::format(
      "const float3 k = (float3)(-0.8660254,0.5,0.57735); float3 pt = abs(p); "
      "pt.xy -= 2.0*min(dot(k.xy,p.xy),0.0)*k.xy; float2 d = "
      "(float2)(length(p.xy-(float2)(clamp(p.x,-k.z*{{%1$s-hexagonal-prism.a}},"
      "k.z*{{%1$s-hexagonal-prism.a}}), "
      "{{%1$s-hexagonal-prism.a}})*sign(p.y-{{%1$s-hexagonal-prism.a}}),p.z-{{%"
      "1$s-hexagonal-prism.b}}); return min(max(d.x, d.y),0.0) + "
      "length(max(d,0.0));",
      this->id_.c_str());
  this->params_[fmt::format("%s-hexagonal-prism.a", this->id_.c_str())] = &a_;
  this->params_[fmt::format("%s-hexagonal-prism.b", this->id_.c_str())] = &b_;
}
