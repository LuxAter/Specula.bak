#ifndef SPECULA_CORE_SPECTRUM_SAMPLED_HPP_
#define SPECULA_CORE_SPECTRUM_SAMPLED_HPP_

#include "coefficient.hpp"
#include "common.hpp"
#include "specula/global.hpp"

namespace specula {
class SampledSpectrum : public CoefficientSpectrum<spectral_samples> {
public:
  SampledSpectrum(Float v = 0.0f) : CoefficientSpectrum<spectral_samples>(v) {}
  SampledSpectrum(const CoefficientSpectrum<spectral_samples> &other)
      : CoefficientSpectrum<spectral_samples>(other) {}
  SampledSpectrum(const RGBSpectrum &other,
                  SpectrumType type = SpectrumType::REFLECTANCE);

  static SampledSpectrum from_rgb(const Float rgb[3],
                                  SpectrumType type = SpectrumType::ILLUMINANT);
  static SampledSpectrum
  from_xyz(const Float xyz[3], SpectrumType type = SpectrumType::REFLECTANCE);
  static SampledSpectrum from_sampled(const Float *lambda, const Float *v,
                                      std::size_t n);

  static void init();

  Float y() const {
    Float yy = 0.0f;
    for (std::size_t i = 0; i < spectral_samples; ++i)
      yy += Y.c[i] * c[i];
    return yy * Float(sampled_lambda_end - sampled_lambda_start) /
           Float(CIE_Y_integral * spectral_samples);
  }
  void to_rgb(Float *rgb) const {
    Float xyz[3];
    to_xyz(xyz);
    xyz_to_rgb(xyz, rgb);
  }
  void to_xyz(Float *xyz) const {
    xyz[0] = xyz[1] = xyz[2] = 0.0f;
    for (std::size_t i = 0; i < spectral_samples; ++i) {
      xyz[0] += X.c[i] * c[i];
      xyz[1] += Y.c[i] * c[i];
      xyz[2] += Z.c[i] * c[i];
    }
    Float scale = Float(sampled_lambda_end - sampled_lambda_start) /
                  Float(CIE_Y_integral * spectral_samples);
    xyz[0] *= scale;
    xyz[1] *= scale;
    xyz[2] *= scale;
  }
  RGBSpectrum to_rgb_spectrum() const;
  SampledSpectrum to_sampled_spectrum() const;

private:
  static SampledSpectrum X, Y, Z;
  static SampledSpectrum rgb_refl_spect_white, rgb_refl_spect_cyan,
      rgb_refl_spect_magenta, rgb_refl_spect_yellow, rgb_refl_spect_red,
      rgb_refl_spect_green, rgb_refl_spect_blue;
  static SampledSpectrum rgb_illum_spect_white, rgb_illum_spect_cyan,
      rgb_illum_spect_magenta, rgb_illum_spect_yellow, rgb_illum_spect_red,
      rgb_illum_spect_green, rgb_illum_spect_blue;
};

inline SampledSpectrum sqrt(const SampledSpectrum &s) {
  SampledSpectrum ret;
  for (typename SampledSpectrum::size_type i = 0; i < spectral_samples; ++i)
    ret[i] = std::sqrt(s[i]);
  CHECK(!ret.has_nans());
  return ret;
}
inline SampledSpectrum pow(const SampledSpectrum &s, Float e) {
  SampledSpectrum ret;
  for (typename SampledSpectrum::size_type i = 0; i < spectral_samples; ++i)
    ret[i] = std::pow(s[i], e);
  CHECK(!ret.has_nans());
  return ret;
}
inline SampledSpectrum exp(const SampledSpectrum &s) {
  SampledSpectrum ret;
  for (typename SampledSpectrum::size_type i = 0; i < spectral_samples; ++i)
    ret[i] = std::exp(s[i]);
  CHECK(!ret.has_nans());
  return ret;
}
inline SampledSpectrum clamp(const SampledSpectrum &s, Float low = 0,
                             Float high = INFTY) {
  SampledSpectrum ret;
  for (typename SampledSpectrum::size_type i = 0; i < spectral_samples; ++i)
    ret[i] = clamp(s[i], low, high);
  CHECK(!ret.has_nans());
  return ret;
}

} // namespace specula

#endif /* end of include guard: SPECULA_CORE_SPECTRUM_SAMPLED_HPP_ */
