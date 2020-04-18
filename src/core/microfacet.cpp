#include "specula/core/microfacet.hpp"
#include "specula/core/reflection.hpp"

namespace specula {
static void beckmann_sample11(Float cos_theta_i, Float u1, Float u2,
                              Float *slope_x, Float *slope_y) {
  if (cos_theta_i > 0.9999f) {
    Float r = std::sqrt(-std::log(1.0f - u1));
    Float sin_phi = std::sin(2 * PI * u2);
    Float cos_phi = std::cos(2 * PI * u2);
    *slope_x = r * cos_phi;
    *slope_y = r * sin_phi;
    return;
  }
  Float sin_theta_i =
      std::sqrt(std::max(Float(0), 1 - cos_theta_i * cos_theta_i));
  Float tan_theta_i = sin_theta_i / cos_theta_i;
  Float cot_theta_i = 1 / tan_theta_i;

  Float a = -1, c = erf(cot_theta_i);
  Float sample_x = std::max(u1, Float(1e-6f));

  Float theta_i = std::acos(cos_theta_i);
  Float fit = 1 + theta_i * (-0.876f + theta_i * (0.4265f - 0.0594f * theta_i));
  Float b = c - (1 + c) * std::pow(1 - sample_x, fit);

  static const Float SQRT_PI_INV = 1.0f / std::sqrt(PI);
  Float normalization =
      1 / (1 + c +
           SQRT_PI_INV * tan_theta_i * std::exp(-cot_theta_i * cot_theta_i));

  int it = 0;
  while (++it < 10) {
    if (!(b >= a && b <= c))
      b = 0.5f * (a + c);
    Float inv_erf = erf_inv(b);
    Float value =
        normalization *
            (1 + b + SQRT_PI_INV * tan_theta_i * std::exp(-inv_erf * inv_erf)) -
        sample_x;
    Float derivative = normalization * (1 - inv_erf * tan_theta_i);

    if (std::abs(value) < 1e-5f)
      break;
    if (value > 0)
      c = b;
    else
      a = b;
    b -= value / derivative;
  }

  *slope_x = erf_inv(b);
  *slope_y = erf_inv(2.0f * std::max(u2, Float(1e-6f)) - 1.0f);
  CHECK(!std::isinf(*slope_x));
  CHECK(!std::isnan(*slope_x));
  CHECK(!std::isinf(*slope_y));
  CHECK(!std::isnan(*slope_y));
}

static specula::Vector3f beckmann_sample(const Vector3f &wi, Float alpha_x,
                                         Float alpha_y, Float u1, Float u2) {
  Vector3f wi_stretched =
      normalize(Vector3f(alpha_x * wi.x, alpha_y * wi.y, wi.z));

  Float slope_x, slope_y;
  beckmann_sample11(cos_theta(wi_stretched), u1, u2, &slope_x, &slope_y);
  Float tmp = cos_phi(wi_stretched) * slope_x - sin_phi(wi_stretched) * slope_y;
  slope_y = sin_phi(wi_stretched) * slope_x + cos_phi(wi_stretched) * slope_y;
  slope_x = tmp;

  slope_x = alpha_x * slope_x;
  slope_y = alpha_y * slope_y;
  return normalize(Vector3f(-slope_x, -slope_y, 1.0f));
}
} // namespace specula

specula::MicrofacetDistribution::~MicrofacetDistribution() {}

specula::Float specula::BeckmannDistribution::d(const Vector3f &wh) const {
  Float tan_theta2 = tan2_theta(wh);
  if (std::isinf(tan_theta2))
    return 0.0f;
  Float cos4_theta = cos2_theta(wh) * cos2_theta(wh);
  return std::exp(-tan_theta2 * (cos2_phi(wh) / (alphax * alphax) +
                                 sin2_phi(wh) / (alphay * alphay))) /
         (PI * alphax * alphay * cos4_theta);
}
specula::Vector3f
specula::BeckmannDistribution::sample_wh(const Vector3f &wo,
                                         const Point2f &u) const {}

specula::Float specula::BeckmannDistribution::lambda(const Vector3f &w) const {}

std::string specula::BeckmannDistribution::fmt() const {}
