#include "light/light.hpp"

#include <limits>

#include "color.hpp"
#include "math/math.hpp"

specula::light::Light::Light(Color c, double i)
    : color(c),
      intensity(i),
      type_(POINT_LIGHT),
      direction_(0.0),
      position_(0.0),
      samples_(16),
      radius_(0.0),
      w_(0.0),
      h_(0.0) {}

specula::light::Light::Light(LightType type, Color c, double i)
    : color(c),
      intensity(i),
      type_(type),
      direction_(0.0),
      position_(0.0),
      samples_(16),
      radius_(0.0),
      w_(0.0),
      h_(0.0) {}
specula::light::Light::Light(LightType type, const math::vec3<double>& va, Color c,
                             double i)
    : color(c),
      intensity(i),
      type_(type),
      direction_(0.0),
      position_(0.0),
      samples_(16),
      radius_(0.0),
      w_(0.0),
      h_(0.0) {
  if (type != DIRECTION_LIGHT) {
    position_ = va;
  } else {
    direction_ = va;
  }
}
specula::light::Light::Light(LightType type, const math::vec3<double>& va,
                             const math::vec3<double>& vb, Color c, double i)
    : color(c),
      intensity(i),
      type_(type),
      direction_(vb),
      position_(va),
      samples_(16),
      radius_(0.0),
      w_(0.0),
      h_(0.0) {}
specula::light::Light::Light(LightType type, const math::vec3<double>& va,
                             const math::vec3<double>& vb, const double& r,
                             std::size_t samples, Color c, double i)
    : color(c),
      intensity(i),
      type_(type),
      direction_(vb),
      position_(va),
      samples_(samples),
      radius_(r),
      w_(0.0),
      h_(0.0) {}
specula::light::Light::Light(LightType type, const math::vec3<double>& va,
                             const math::vec3<double>& vb, const double& w,
                             const double& h, std::size_t samples, Color c,
                             double i)
    : color(c),
      intensity(i),
      type_(type),
      direction_(vb),
      position_(va),
      samples_(samples),
      radius_(0.0),
      w_(w),
      h_(h) {}

void specula::light::Light::Translate(const math::vec3<double>& trans) {
  position_ += trans;
}
void specula::light::Light::SetPosition(const math::vec3<double>& pos) {
  position_ = pos;
}
void specula::light::Light::SetDirection(const math::vec3<double>& dir) {
  direction_ = dir;
}

void specula::light::Light::Illuminate(const math::vec3<double>& p,
                                       math::vec3<double>& dir,
                                       math::vec3<double>& val, double& dist) {
  switch (type_) {
    case POINT_LIGHT:
    case CIRCLE_LIGHT:
    case RECT_LIGHT:
      dir = p - position_;
      dist = math::length(dir);
      dir /= dist;
      if (intensity == -1) {
        val =
            color * math::clamp(intensity / (4.0 * M_PI * math::pow(dist, 2.0)),
                                0.0, 1.0);
      } else {
        val = color;
      }
      break;
    case DIRECTION_LIGHT:
      dir = direction_;
      val = color * ((intensity == -1) ? 1 : intensity);
      dist = std::numeric_limits<double>::infinity();
      break;
  }
}
