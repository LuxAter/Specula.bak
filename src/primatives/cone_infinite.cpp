#define GLM_FORCE_SWIZZLE
#include "specula/primatives/cone_infinite.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::InfiniteCone::InfiniteCone(const float &alpha)
    : Primative([this](const glm::vec3 &p) {
        float q = glm::length(p.xy());
        return glm::dot(this->cone_, glm::vec2(q, p.z));
      }),
      // cone_(std::sin(alpha), std::cos(alpha)) {
      cone_(std::cos(alpha), std::sin(alpha)) {
  this->source_ = fmt::format(
      "float q = length(p.xy); return dot({{%1$s-cone}},(float2)(q,p.z));",
      this->id_.c_str());
  this->params_[fmt::format("%s-cone", this->id_.c_str())] = &cone_;
}
