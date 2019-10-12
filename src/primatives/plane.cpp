#define GLM_FORCE_SWIZZLE
#include "specula/primatives/plane.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::Plane::Plane(const float &x, const float &y, const float &z,
                      const float &w)
    : Primative([this](const glm::vec3 &p) {
        return glm::dot(p, this->normal_.xyz()) + this->normal_.w;
      }),
      normal_(glm::normalize(glm::vec4(x, y, z, w))) {
  this->source_ = fmt::format("return dot(p,{{%1$s-plane}}) - {{%1$s-plane.w}};",
                              this->id_.c_str());
  this->params_[fmt::format("%s-plane", this->id_.c_str())] = &normal_;
  this->params_[fmt::format("%s-plane.w", this->id_.c_str())] = &normal_.w;
}
