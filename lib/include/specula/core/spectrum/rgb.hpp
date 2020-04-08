#ifndef SPECULA_CORE_SPECTRUM_RGB_HPP_
#define SPECULA_CORE_SPECTRUM_RGB_HPP_

#include "coefficient.hpp"
#include "common.hpp"
#include "specula/global.hpp"

namespace specula {
class RGBSpectrum : public CoefficientSpectrum<3> {
  using CoefficientSpectrum<3>::c;

public:
  RGBSpectrum(Float v = 0.0f) : CoefficientSpectrum<3>(v) {}
  RGBSpectrum(const CoefficientSpectrum<3> &v) : CoefficientSpectrum<3>(v) {}
  // RGBSpectrum(const RGBSpectrum &v) : CoefficientSpectrum<3>(v.c) {}
  RGBSpectrum(const RGBSpectrum &s, SpectrumType )
      : CoefficientSpectrum<3>(static_cast<CoefficientSpectrum<3>>(s)) {}

  static RGBSpectrum from_rgb(const Float rgb[3],
                              SpectrumType = SpectrumType::REFLECTANCE) {
    RGBSpectrum s;
    s.c[0] = rgb[0];
    s.c[1] = rgb[1];
    s.c[2] = rgb[2];
    CHECK(!s.has_nans());
    return s;
  }
  static RGBSpectrum from_xyz(const Float xyz[3],
                              SpectrumType = SpectrumType::REFLECTANCE) {
    RGBSpectrum s;
    xyz_to_rgb(xyz, s.c);
    CHECK(!s.has_nans());
    return s;
  }
  static RGBSpectrum from_sampled(const Float *lambda, const Float *v,
                                  std::size_t n) {
    if (!spectrum_samples_sorted(lambda, v, n)) {
      std::vector<Float> sorted_lambda(&lambda[0], &lambda[n]);
      std::vector<Float> sorted_v(&v[0], &v[n]);
      sort_spectrum_samples(&sorted_lambda[0], &sorted_v[0], n);
      return from_sampled(&sorted_lambda[0], &sorted_v[0], n);
    }
    Float xyz[3] = {0, 0, 0};
    for (std::size_t i = 0; i < CIE_samples; ++i) {
      Float val = interpolate_spectrum_samples(lambda, v, n, CIE_lambda[i]);
      xyz[0] += val * CIE_X[i];
      xyz[1] += val * CIE_Y[i];
      xyz[2] += val * CIE_Z[i];
    }
    Float scale = Float(CIE_lambda[CIE_samples - 1] - CIE_lambda[0]) /
                  Float(CIE_Y_integral * CIE_samples);
    xyz[0] *= scale;
    xyz[1] *= scale;
    xyz[2] *= scale;
    return from_xyz(xyz);
  }

  Float y() const {
    const Float y_weight[3] = {0.212671f, 0.715160f, 0.072169f};
    return y_weight[0] * c[0] + y_weight[1] * c[1] + y_weight[2] * c[2];
  }
  void to_rgb(Float *rgb) const {
    rgb[0] = c[0];
    rgb[1] = c[1];
    rgb[2] = c[2];
  }
  void to_xyz(Float *xyz) const { rgb_to_xyz(c, xyz); }
  RGBSpectrum to_rgb_spectrum() const { return *this; }
  SampledSpectrum to_sampled_spectrum() const;
};

inline RGBSpectrum sqrt(const RGBSpectrum &s) {
  RGBSpectrum ret;
  for (typename RGBSpectrum::size_type i = 0; i < 3; ++i)
    ret[i] = std::sqrt(s[i]);
  CHECK(!ret.has_nans());
  return ret;
}
inline RGBSpectrum pow(const RGBSpectrum &s, Float e) {
  RGBSpectrum ret;
  for (typename RGBSpectrum::size_type i = 0; i < 3; ++i)
    ret[i] = std::pow(s[i], e);
  CHECK(!ret.has_nans());
  return ret;
}
inline RGBSpectrum exp(const RGBSpectrum &s) {
  RGBSpectrum ret;
  for (typename RGBSpectrum::size_type i = 0; i < 3; ++i)
    ret[i] = std::exp(s[i]);
  CHECK(!ret.has_nans());
  return ret;
}
inline RGBSpectrum clamp(const RGBSpectrum &s, Float low = 0,
                         Float high = INFTY) {
  RGBSpectrum ret;
  for (typename RGBSpectrum::size_type i = 0; i < 3; ++i)
    ret[i] = clamp(s[i], low, high);
  CHECK(!ret.has_nans());
  return ret;
}

} // namespace specula

#endif /* end of include guard: SPECULA_CORE_SPECTRUM_RGB_HPP_ */
