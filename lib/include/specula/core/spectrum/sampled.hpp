#ifndef SPECULA_CORE_SPECTRUM_SAMPLED_HPP_
#define SPECULA_CORE_SPECTRUM_SAMPLED_HPP_

#include "coefficient.hpp"
#include "common.hpp"
#include "global/declarations.hpp"
#include "specula/global.hpp"

namespace specula {
class SampledSpectrum : public CoefficientSpectrum<spectral_samples> {
  SampledSpectrum(Float v = 0.0f) : CoefficientSpectrum<spectral_samples>(v) {}
  SampledSpectrum(const CoefficientSpectrum<spectral_samples> &v)
      : CoefficientSpectrum<spectral_samples>(v) {}
  SampledSpectrum(const RGBSpectrum &r,
                  SpectrumType type = SpectrumType::REFLECTANCE);

  static SampledSpectrum from_sampled(const Float *lambda, const Float *v,
                                      std::size_t n) {
    if (!spectrum_samples_sorted(lambda, v, n)) {
      std::vector<Float> sorted_lambda(&lambda[0], &lambda[n]);
      std::vector<Float> sorted_v(&v[0], &v[n]);
      sort_spectrum_samples(&sorted_lambda[0], &sorted_v[0], n);
      return from_sampled(&sorted_lambda[0], &sorted_v[0], n);
    }
    SampledSpectrum r;
    for (typename CoefficientSpectrum<spectral_samples>::size_type i = 0;
         i < spectral_samples; ++i) {
      Float lambda0 = lerp(Float(i) / Float(spectral_samples),
                           sampled_lambda_start, sampled_lambda_end);
      Float lambda1 = lerp(Float(i + 1) / Float(spectral_samples),
                           sampled_lambda_start, sampled_lambda_end);
      r.c[i] = average_spectrum_samples(lambda, v, n, lambda0, lambda1);
    }
    return r;
  }
  static void init() {
    for (typename CoefficientSpectrum<spectral_samples>::size_type i = 0;
         i < spectral_samples; ++i) {
      Float wl0 = lerp(Float(i) / Float(spectral_samples), sampled_lambda_start,
                       sampled_lambda_end);
      Float wl1 = lerp(Float(i + 1) / Float(spectral_samples),
                       sampled_lambda_start, sampled_lambda_end);
      X.c[i] =
          average_spectrum_samples(CIE_lambda, CIE_X, CIE_samples, wl0, wl1);
      Y.c[i] =
          average_spectrum_samples(CIE_lambda, CIE_Y, CIE_samples, wl0, wl1);
      Z.c[i] =
          average_spectrum_samples(CIE_lambda, CIE_Z, CIE_samples, wl0, wl1);

      rgb_refl_spect_white.c[i] = average_spectrum_samples(
          RGB_spect_lambda, RGB_refl_spect_white, RGB_spect_samples, wl0, wl1);
      rgb_refl_spect_cyan.c[i] = average_spectrum_samples(
          RGB_spect_lambda, RGB_refl_spect_cyan, RGB_spect_samples, wl0, wl1);
      rgb_refl_spect_magenta.c[i] =
          average_spectrum_samples(RGB_spect_lambda, RGB_refl_spect_magenta,
                                   RGB_spect_samples, wl0, wl1);
      rgb_refl_spect_yellow.c[i] = average_spectrum_samples(
          RGB_spect_lambda, RGB_refl_spect_yellow, RGB_spect_samples, wl0, wl1);
      rgb_refl_spect_red.c[i] = average_spectrum_samples(
          RGB_spect_lambda, RGB_refl_spect_red, RGB_spect_samples, wl0, wl1);
      rgb_refl_spect_green.c[i] = average_spectrum_samples(
          RGB_spect_lambda, RGB_refl_spect_green, RGB_spect_samples, wl0, wl1);
      rgb_refl_spect_blue.c[i] = average_spectrum_samples(
          RGB_spect_lambda, RGB_refl_spect_blue, RGB_spect_samples, wl0, wl1);

      rgb_illum_spect_white.c[i] = average_spectrum_samples(
          RGB_spect_lambda, RGB_illum_spect_white, RGB_spect_samples, wl0, wl1);
      rgb_illum_spect_cyan.c[i] = average_spectrum_samples(
          RGB_spect_lambda, RGB_illum_spect_cyan, RGB_spect_samples, wl0, wl1);
      rgb_illum_spect_magenta.c[i] =
          average_spectrum_samples(RGB_spect_lambda, RGB_illum_spect_magenta,
                                   RGB_spect_samples, wl0, wl1);
      rgb_illum_spect_yellow.c[i] =
          average_spectrum_samples(RGB_spect_lambda, RGB_illum_spect_yellow,
                                   RGB_spect_samples, wl0, wl1);
      rgb_illum_spect_red.c[i] = average_spectrum_samples(
          RGB_spect_lambda, RGB_illum_spect_red, RGB_spect_samples, wl0, wl1);
      rgb_illum_spect_green.c[i] = average_spectrum_samples(
          RGB_spect_lambda, RGB_illum_spect_green, RGB_spect_samples, wl0, wl1);
      rgb_illum_spect_blue.c[i] = average_spectrum_samples(
          RGB_spect_lambda, RGB_illum_spect_blue, RGB_spect_samples, wl0, wl1);
    }
  }

  void to_xyz(Float xyz[3]) const {
    xyz[0] = xyz[1] = xyz[2] = 0.0f;
    for (typename CoefficientSpectrum<spectral_samples>::size_type i = 0;
         i < spectral_samples; ++i) {
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
  Float y() const {
    Float yy = 0.0f;
    for (typename CoefficientSpectrum<spectral_samples>::size_type i = 0;
         i < spectral_samples; ++i)
      yy += Y.c[i] * c[i];
    return yy * Float(sampled_lambda_end - sampled_lambda_start) /
           Float(CIE_Y_integral * spectral_samples);
  }
  void to_rgb(Float rgb[3]) const {
    Float xyz[3];
    to_xyz(xyz);
    xyz_to_rgb(xyz, rgb);
  }
  RGBSpectrum to_rgb_spectrum() const;

  static SampledSpectrum from_rgb(const Float rgb[3],
                                  SpectrumType type = SpectrumType::ILLUMINANT);
  static SampledSpectrum
  from_xyz(const Float xyz[3], SpectrumType type = SpectrumType::REFLECTANCE) {
    Float rgb[3];
    xyz_to_rgb(xyz, rgb);
    return from_rgb(rgb, type);
  }

private:
  static SampledSpectrum X, Y, Z;
  static SampledSpectrum rgb_refl_spect_white, rgb_refl_spect_cyan,
      rgb_refl_spect_magenta, rgb_refl_spect_yellow, rgb_refl_spect_red,
      rgb_refl_spect_green, rgb_refl_spect_blue;
  static SampledSpectrum rgb_illum_spect_white, rgb_illum_spect_cyan,
      rgb_illum_spect_magenta, rgb_illum_spect_yellow, rgb_illum_spect_red,
      rgb_illum_spect_green, rgb_illum_spect_blue;
};
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_SPECTRUM_SAMPLED_HPP_ */
