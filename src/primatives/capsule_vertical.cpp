#include "specula/primatives/capsule_vertical.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::VerticalCapsule::VerticalCapsule(const float &h, const float &r)
    : Primative([this](const glm::vec3 &p) {
        glm::vec3 pt(p.x, p.y - glm::clamp(p.y, 0.0f, this->height_), p.z);
        return length(pt) - this->radius_;
      }),
      height_(h), radius_(r) {
  this->source_ = fmt::format("float3 pt = (float3)(p.x, p.y - clamp(p.y, 0.0, "
                              "{{%1$s-vertical-capsule.height}}), p.z); return "
                              "length(pt) - {{%1$s-vertical-capsule.radius}};",
                              this->id_.c_str());
  this->params_[fmt::format("%s-vertical-capsule.height", this->id_.c_str())] =
      &height_;
  this->params_[fmt::format("%s-vertical-capsule.radius", this->id_.c_str())] =
      &radius_;
}
