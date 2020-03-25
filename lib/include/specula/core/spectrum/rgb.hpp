#ifndef SPECULA_CORE_SPECTRUM_RGB_HPP_
#define SPECULA_CORE_SPECTRUM_RGB_HPP_

#include "coefficient.hpp"
#include "common.hpp"
#include "global/declarations.hpp"
#include "specula/global.hpp"

namespace specula {
class RGBSpectrum : public CoefficientSpectrum<3> {
  using CoefficientSpectrum<3>::c;

public:
  RGBSpectrum(Float v = 0.0f) : CoefficientSpectrum<3>(v) {}
  RGBSpectrum(const CoefficientSpectrum<3> &v) : CoefficientSpectrum<3>(v) {}
  RGBSpectrum(const RGBSpectrum &s,
              SpectrumType type = SpectrumType::REFLECTANCE) {
    *this = s;
  }

  static RGBSpectrum from_rgb(const Float rgb[3],
                              SpectrumType type = SpectrumType::REFLECTANCE) {
    RGBSpectrum s;
    s.c[0] = rgb[0];
    s.c[1] = rgb[1];
    s.c[2] = rgb[2];
    CHECK(!s.has_nans());
    return s;
  }
  void to_rgb(Float *rgb) const {
    rgb[0] = c[0];
    rgb[1] = c[1];
    rgb[2] = c[2];
  }
  const RGBSpectrum &to_rgb_spectrum() const { return *this; }
  void to_xyz(Float xyz[3]) const { rgb_to_xyz(c, xyz); }
  static RGBSpectrum from_xyz(const Float xyz[3],
                              SpectrumType type = SpectrumType::REFLECTANCE) {
    RGBSpectrum r;
    xyz_to_rgb(xyz, r.c);
    return r;
  }
  Float y() const {
    const Float y_weight[3] = {0.212671f, 0.715160f, 0.072169f};
    return y_weight[0] * c[0] + y_weight[1] * c[1] + y_weight[2] * c[2];
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
};

} // namespace specula

#endif /* end of include guard: SPECULA_CORE_SPECTRUM_RGB_HPP_ */
