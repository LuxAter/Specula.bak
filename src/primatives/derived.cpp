#include "specula/primatives/derived.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::DerivedPrimative::DerivedPrimative(const std::shared_ptr<Primative> &a,
                                            const std::shared_ptr<Primative> &b,
                                            const DerivedTypes &type, float r)
    : Primative(), a_(a), b_(b), radius_(r) {
  switch (type) {
  case UNION:
    this->distance_ = [this](const glm::vec3 &p) {
      return glm::min(this->a_->distance(p), this->b_->distance(p));
    };
    break;
  case SUBTRACTION:
    this->distance_ = [this](const glm::vec3 &p) {
      return glm::max(-this->a_->distance(p), this->b_->distance(p));
    };
    break;
  case INTERSECTION:
    this->distance_ = [this](const glm::vec3 &p) {
      return glm::max(this->a_->distance(p), this->b_->distance(p));
    };
    break;
  case SMOOTH_UNION:
    this->distance_ = [this](const glm::vec3 &p) {
      float d1 = this->a_->distance(p);
      float d2 = this->b_->distance(p);
      float h = glm::clamp(0.5f + 0.5f * (d2 - d1) / k, 0.0f, 1.0f);
      return glm::mix(d2, d1, h) - k * h * (1.0f - h);
    };
    break;
  case SMOOTH_SUBTRACTION:
    this->distance_ = [this](const glm::vec3 &p) {
      float d1 = this->a_->distance(p);
      float d2 = this->b_->distance(p);
      float h = glm::clamp(0.5f - 0.5f * (d2 + d1) / k, 0.0f, 1.0f);
      return glm::mix(d2, -d1, h) + k * h * (1.0f - h);
    };
    break;
  case SMOOTH_INTERSECTION:
    this->distance_ = [this](const glm::vec3 &p) {
      float d1 = this->a_->distance(p);
      float d2 = this->b_->distance(p);
      float h = glm::clamp(0.5f - 0.5f * (d2 - d1) / k, 0.0f, 1.0f);
      return glm::mix(d2, d1, h) + k * h * (1.0f - h);
    };
    break;
  }
}
