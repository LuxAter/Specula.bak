#include "specula/primatives/box.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::Box::Box(const float &w, const float &l, const float &h)
    : Primative([this](const glm::vec3 &p) {
        glm::vec3 d = glm::abs(p) - this->box_;
        return glm::length(glm::max(d, 0.0f)) +
               glm::min(glm::max(d.x, glm::max(d.y, d.z)), 0.0f);
      }),
      box_(w, l, h) {
  this->source_ =
      fmt::format("float3 d = abs(p) - {{%s-box}}; return length(max(d,0.0)) + "
                  "min(max(d.x,max(d,y,d.z)),0.0);",
                  this->id_.c_str());
  this->params_[fmt::format("%s-box", this->id_.c_str())] = &box_;
}
