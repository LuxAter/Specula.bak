#include "specula/primatives/rounded.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::RoundedPrimative::RoundedPrimative(
    const std::shared_ptr<Primative> &base, const float &r)
    : Primative([this](const glm::vec3 &p) {
        return this->base_->distance_(p) - this->radius_;
      }),
      radius_(r), base_(base) {}
