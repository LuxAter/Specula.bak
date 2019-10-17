#define GLM_FORCE_SWIZZLE
#include "specula/primatives/torus_capped.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::CappedTorus::CappedTorus(const float &r_big, const float &r_small,
                                  const float &ra, const float &rb)
    : Primative([this](const glm::vec3 &p) {
        glm::vec3 pt(glm::abs(p.x), p.y, p.z);
        float k = (this->torus_.y * pt.x > this->torus_.x * pt.y)
                      ? glm::dot(pt.xy(), this->torus_)
                      : glm::length(pt.xy());
        return glm::sqrt(glm::dot(pt, pt) + this->ra_ * this->ra_ -
                         2.0 * this->ra_ * k) -
               this->rb_;
      }),
      torus_(r_big, r_small), ra_(ra), rb_(rb) {
  this->source_ = fmt::format(
      "p.x = fabs(p.x); float k = ({{%1$s-torus.y}}*p.x>{{%1$s-torus.x}}*p.y) ? "
      "dot(p.xy, {{%1$s-torus}} : length(p.xy); return sqrt(dot(p,p) + "
      "{{%1$s-torus.ra}}*{{%1$s-torus.ra}}-2.0f*{{%1$s-torus.ra}}*k)-{{%1$s-"
      "torus.rb}};",
      this->id_.c_str());
  this->params_[fmt::format("%s-torus", this->id_.c_str())] = &torus_;
  this->params_[fmt::format("%s-torus.x", this->id_.c_str())] = &torus_.x;
  this->params_[fmt::format("%s-torus.y", this->id_.c_str())] = &torus_.y;
  this->params_[fmt::format("%s-torus.ra", this->id_.c_str())] = &ra_;
  this->params_[fmt::format("%s-torus.rb", this->id_.c_str())] = &rb_;
}
