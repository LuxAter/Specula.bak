#include "specula/core/microfacet.hpp"
#include "core/geometry/common.hpp"
#include "specula/core/reflection.hpp"
#include <math.h>

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

static void trowbridge_reitz_sample11(Float cos_theta_i, Float u1, Float u2,
                                      Float *slope_x, Float *slope_y) {
  if (cos_theta_i > 0.9999) {
    Float r = std::sqrt(u1 / (1 - u1));
    Float phi = 6.28318530718 * u2;
    *slope_x = r * std::cos(phi);
    *slope_y = r * std::sin(phi);
    return;
  }

  Float sin_theta_i =
      std::sqrt(std::max(Float(0), 1 - cos_theta_i * cos_theta_i));
  Float tan_theta_i = sin_theta_i / cos_theta_i;
  Float a = 1 / tan_theta_i;
  Float g1 = 2 / (1 + std::sqrt(1.0f + 1.0f / (a * a)));

  Float A = 2 * u1 / g1 - 1;
  Float tmp = 1.0f / (A * A - 1.0f);
  if (tmp > 1e10)
    tmp = 1e10;
  Float b = tan_theta_i;
  float d = std::sqrt(
      std::max(Float(b * b * tmp * tmp - (A * A - b * b) * tmp), Float(0)));
  Float slope_x_1 = b * tmp - d;
  Float slope_x_2 = b * tmp + d;
  *slope_x = (A < 0 || slope_x_2 > 1.0f / tan_theta_i) ? slope_x_1 : slope_x_2;

  Float s;
  if (u2 > 0.5f) {
    s = 1.0f;
    u2 = 2.0f * (u2 - 0.5f);
  } else {
    s = -1.0f;
    u2 = 2.0f * (0.5f - u2);
  }
  Float z = (u2 * (u2 * (u2 * 0.27385f - 0.73369f) + 0.46351f)) /
            (u2 * (u2 * (u2 * 0.093073f + 0.309420f) - 1.000000f) + 0.597999f);
  *slope_y = s * z * std::sqrt(1.0f + *slope_x * *slope_x);
  CHECK(!std::isinf(*slope_y));
  CHECK(!std::isnan(*slope_y));
}

static Vector3f trowbridge_reitz_sample(const Vector3f &wi, Float alpha_x,
                                        Float alpha_y, Float u1, Float u2) {
  Vector3f wi_stretched =
      normalize(Vector3f(alpha_x * wi.x, alpha_y * wi.y, wi.z));
  Float slope_x, slope_y;
  trowbridge_reitz_sample11(cos_theta(wi_stretched), u1, u2, &slope_x,
                            &slope_y);

  Float tmp = cos_phi(wi_stretched) * slope_x - sin_phi(wi_stretched) * slope_y;
  slope_y = sin_phi(wi_stretched) * slope_x + cos_phi(wi_stretched) * slope_y;
  slope_x = tmp;

  slope_x = alpha_x * slope_x;
  slope_y = alpha_y * slope_y;

  return normalize(Vector3f(-slope_x, -slope_y, 1.0f));
}
} // namespace specula

specula::MicrofacetDistribution::~MicrofacetDistribution() {}

specula::Float specula::MicrofacetDistribution::pdf(const Vector3f &wo,
                                                    const Vector3f &wh) const {
  if (sample_visible_area) {
    return d(wh) * g1(wo) * abs_dot(wo, wh) / abs_cos_theta(wo);
  } else {
    return d(wh) * abs_cos_theta(wh);
  }
}

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
                                         const Point2f &u) const {
  if (!sample_visible_area) {
    Float tan_theta2, phi;
    if (alphax == alphay) {
      Float log_sample = std::log(1 - u[0]);
      CHECK(!std::isinf(log_sample));
      tan_theta2 = -alphax * alphax * log_sample;
      phi = u[1] * 2 * PI;
    } else {
      Float log_sample = std::log(1 - u[0]);
      CHECK(!std::isinf(log_sample));
      phi = std::atan(alphay / alphax * std::tan(2 * PI * u[1] + 0.5f * PI));
      if (u[1] > 0.5f)
        phi += PI;
      Float sin_phi = std::sin(phi), cos_phi = std::cos(phi);
      Float alphax2 = alphax * alphax, alphay2 = alphay * alphay;
      tan_theta2 = -log_sample /
                   (cos_phi * cos_phi / alphax2 + sin_phi * sin_phi / alphay2);
    }
    Float cos_theta = 1 / std::sqrt(1 + tan_theta2);
    Float sin_theta = std::sqrt(std::max(Float(0), 1 - cos_theta * cos_theta));
    Vector3f wh = spherical_direction(sin_theta, cos_theta, phi);
    if (!same_hemisphere(wo, wh))
      wh = -wh;
    return wh;
  } else {
    Vector3f wh;
    bool flip = wo.z < 0;
    wh = beckmann_sample(flip ? -wo : wo, alphax, alphay, u[0], u[1]);
    if (flip)
      wh = -wh;
    return wh;
  }
}

specula::Float specula::BeckmannDistribution::lambda(const Vector3f &w) const {
  Float abs_tan_theta = std::abs(tan_theta(w));
  if (std::isinf(abs_tan_theta))
    return 0.0f;
  Float alpha =
      std::sqrt(cos2_phi(w) * alphax * alphax + sin2_phi(w) * alphay * alphay);
  Float a = 1 / (alpha * abs_tan_theta);
  if (a >= 1.6f)
    return 0;
  return (1 - 1.259f * a + 0.396f * a * a) / (3.535f * a + 2.181f * a * a);
}

std::string specula::BeckmannDistribution::fmt() const {
  return fmt::format(
      "<MicrofacetDistribution.BeckmannDistribution alphax: {}, alphay: {}>",
      alphax, alphay);
}

specula::Float
specula::TrowbridgeReitzDistribution::d(const Vector3f &wh) const {
  Float tan_theta2 = tan2_theta(wh);
  if (std::isinf(tan_theta2))
    return 0.0f;
  const Float cos4_theta = cos2_theta(wh) * cos2_theta(wh);
  Float e =
      (cos2_phi(wh) / (alphax * alphax) + sin2_phi(wh) / (alphay * alphay)) *
      tan_theta2;
  return 1 / (PI * alphax * alphay * cos4_theta * (1 + e) * (1 + e));
}
specula::Vector3f
specula::TrowbridgeReitzDistribution::sample_wh(const Vector3f &wo,
                                                const Point2f &u) const {
  Vector3f wh;
  if (!sample_visible_area) {
    Float cos_theta_i = 0, phi = (2 * PI) * u[1];
    if (alphax == alphay) {
      Float tan_theta2 = alphax * alphax * u[0] / (1.0f - u[0]);
      cos_theta_i = 1 / std::sqrt(1 + tan_theta2);
    } else {
      phi = std::atan(alphay / alphax * std::tan(2 * PI * u[1] + 0.5f * PI));
      if (u[1] > 0.5f)
        phi += PI;
      Float sin_phi_i = std::sin(phi), cos_phi_i = std::cos(phi);
      const Float alphax2 = alphax * alphax, alphay2 = alphay * alphay;
      const Float alpha2 = 1 / (cos_phi_i * cos_phi_i / alphax2 +
                                sin_phi_i * sin_phi_i / alphay2);
      Float tan_theta2 = alpha2 * u[0] / (1 - u[0]);
      cos_theta_i = 1 / std::sqrt(1 + tan_theta2);
    }
    Float sin_theta_i =
        std::sqrt(std::max(Float(0), 1 - cos_theta_i * cos_theta_i));
    wh = spherical_direction(sin_theta_i, cos_theta_i, phi);
    if (!same_hemisphere(wo, wh))
      wh = -wh;
  } else {
    bool flip = wo.z < 0;
    wh = trowbridge_reitz_sample(flip ? -wo : wo, alphax, alphay, u[0], u[1]);
    if (flip)
      wh = -wh;
  }
  return wh;
}

specula::Float
specula::TrowbridgeReitzDistribution::lambda(const Vector3f &w) const {
  Float abs_tan_theta = std::abs(tan_theta(w));
  if (std::isinf(abs_tan_theta))
    return 0.0f;
  Float alpha =
      std::sqrt(cos2_phi(w) * alphax * alphax + sin2_phi(w) * alphay * alphay);
  Float alpha2_tan2_theta = (alpha * abs_tan_theta) * (alpha * abs_tan_theta);
  return (-1 + std::sqrt(1.0f + alpha2_tan2_theta)) / 2;
}

std::string specula::TrowbridgeReitzDistribution::fmt() const {
  return fmt::format("<MicrofacetDistribution.TrowbridgeReitzDistribution "
                     "alphax: {}, alphay: {}>",
                     alphax, alphay);
}
