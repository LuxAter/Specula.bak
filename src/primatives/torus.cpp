#define GLM_FORCE_SWIZZLE
#include "specula/primatives/torus.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::Torus::Torus(const float &r_big, const float &r_small)
    : Primative([this](const glm::vec3 &p) {
        glm::vec2 q = glm::vec2(glm::length(p.xz()) - this->torus_.x, p.y);
        return glm::length(q) - this->torus_.y;
      }),
      torus_(r_big, r_small) {
  this->source_ =
      fmt::format("float2 q = (float2)(length(p.xz) - {{%1$s-torus.x}}, p.y); "
                  "return length(q) - {{%1$s-torus.y}};",
                  this->id_.c_str());
  this->params_[fmt::format("%s-torus.x", this->id_.c_str())] = &torus_.x;
  this->params_[fmt::format("%s-torus.y", this->id_.c_str())] = &torus_.y;
}
