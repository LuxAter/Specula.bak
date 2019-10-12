#include "specula/primatives/temf.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::tem::tem(const float &r)
    : Primative([this](const glm::vec3 &p) {
        return glm::length(p) - this->radius_;
      }),
      radius_(r) {
  this->source_ =
      fmt::format("", this->id_.c_str());
  this->params_[fmt::format("%s-torus.x", this->id_.c_str())] = &torus_.x;
}
