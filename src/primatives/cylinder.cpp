#define GLM_FORCE_SWIZZLE
#include "specula/primatives/cylinder.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::Cylinder::Cylinder(const float &r)
    : Primative([this](const glm::vec3 &p) {
        return glm::length(p.xz()) - this->radius_;
      }),
      radius_(r) {
  this->source_ = fmt::format("return length(p.xz)-{{%1$s-cylinder.radius}};",
                              this->id_.c_str());
  this->params_[fmt::format("%s-cylinder.radius", this->id_.c_str())] =
      &radius_;
}
