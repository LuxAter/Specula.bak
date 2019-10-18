#define GLM_FORCE_SWIZZLE
#include "specula/primatives/cone_round.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::RoundCone::RoundCone(const float &h, const float &r1, const float &r2)
    : Primative([this](const glm::vec3 &p) {
        glm::vec2 q(glm::length(p.xz()), p.y);
        float b = (this->r1_ - this->r2_) / this->height_;
        float a = glm::sqrt(1.0f - b * b);
        float k = glm::dot(q, glm::vec2(-b, a));
        if (k < 0.0f)
          return glm::length(q) - this->r1_;
        if (k > a * this->height_)
          return glm::length(q - glm::vec2(0.0f, this->height_)) - this->r2_;
        return glm::dot(q, glm::vec2(a, b)) - this->r1_;
      }),
      height_(h), r1_(r1), r2_(r2) {}
