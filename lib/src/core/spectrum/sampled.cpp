#include "specula/core/spectrum/sampled.hpp"
#include "core/spectrum/coefficient.hpp"
#include "core/spectrum/common.hpp"
#include "global/declarations.hpp"
#include "specula/core/spectrum/rgb.hpp"

specula::SampledSpectrum specula::SampledSpectrum::X,
    specula::SampledSpectrum::Y, specula::SampledSpectrum::Z;
specula::SampledSpectrum specula::SampledSpectrum::rgb_refl_spect_white,
    specula::SampledSpectrum::rgb_refl_spect_cyan,
    specula::SampledSpectrum::rgb_refl_spect_magenta,
    specula::SampledSpectrum::rgb_refl_spect_yellow,
    specula::SampledSpectrum::rgb_refl_spect_red,
    specula::SampledSpectrum::rgb_refl_spect_green,
    specula::SampledSpectrum::rgb_refl_spect_blue;
specula::SampledSpectrum specula::SampledSpectrum::rgb_illum_spect_white,
    specula::SampledSpectrum::rgb_illum_spect_cyan,
    specula::SampledSpectrum::rgb_illum_spect_magenta,
    specula::SampledSpectrum::rgb_illum_spect_yellow,
    specula::SampledSpectrum::rgb_illum_spect_red,
    specula::SampledSpectrum::rgb_illum_spect_green,
    specula::SampledSpectrum::rgb_illum_spect_blue;

specula::SampledSpectrum specula::SampledSpectrum::from_rgb(const Float rgb[3],
                                                            SpectrumType type) {
  SampledSpectrum r;
  if (type == SpectrumType::REFLECTANCE) {
    if (rgb[0] <= rgb[1] && rgb[0] <= rgb[2]) {
      r += rgb[0] * rgb_refl_spect_white;
      if (rgb[1] <= rgb[2]) {
        r += (rgb[1] - rgb[0]) * rgb_refl_spect_cyan;
        r += (rgb[2] - rgb[1]) * rgb_refl_spect_blue;
      } else {
        r += (rgb[2] - rgb[0]) * rgb_refl_spect_cyan;
        r += (rgb[1] - rgb[2]) * rgb_refl_spect_green;
      }
    } else if (rgb[1] <= rgb[0] && rgb[1] <= rgb[2]) {
      r += rgb[1] * rgb_refl_spect_white;
      if (rgb[0] <= rgb[2]) {
        r += (rgb[0] - rgb[1]) * rgb_refl_spect_magenta;
        r += (rgb[2] - rgb[0]) * rgb_refl_spect_blue;
      } else {
        r += (rgb[2] - rgb[1]) * rgb_refl_spect_magenta;
        r += (rgb[0] - rgb[1]) * rgb_refl_spect_red;
      }
    } else {
      r += rgb[2] * rgb_refl_spect_white;
      if (rgb[0] <= rgb[1]) {
        r += (rgb[0] - rgb[2]) * rgb_refl_spect_yellow;
        r += (rgb[1] - rgb[0]) * rgb_refl_spect_green;
      } else {
        r += (rgb[1] - rgb[2]) * rgb_refl_spect_yellow;
        r += (rgb[0] - rgb[1]) * rgb_refl_spect_red;
      }
    }
    r *= 0.94;
  } else {
    if (rgb[0] <= rgb[1] && rgb[0] <= rgb[2]) {
      r += rgb[0] * rgb_illum_spect_white;
      if (rgb[1] <= rgb[2]) {
        r += (rgb[1] - rgb[0]) * rgb_illum_spect_cyan;
        r += (rgb[2] - rgb[1]) * rgb_illum_spect_blue;
      } else {
        r += (rgb[2] - rgb[0]) * rgb_illum_spect_cyan;
        r += (rgb[1] - rgb[2]) * rgb_illum_spect_green;
      }
    } else if (rgb[1] <= rgb[0] && rgb[1] <= rgb[2]) {
      r += rgb[1] * rgb_illum_spect_white;
      if (rgb[0] <= rgb[2]) {
        r += (rgb[0] - rgb[1]) * rgb_illum_spect_magenta;
        r += (rgb[2] - rgb[0]) * rgb_illum_spect_blue;
      } else {
        r += (rgb[2] - rgb[1]) * rgb_illum_spect_magenta;
        r += (rgb[0] - rgb[1]) * rgb_illum_spect_red;
      }
    } else {
      r += rgb[2] * rgb_illum_spect_white;
      if (rgb[0] <= rgb[1]) {
        r += (rgb[0] - rgb[2]) * rgb_illum_spect_yellow;
        r += (rgb[1] - rgb[0]) * rgb_illum_spect_green;
      } else {
        r += (rgb[1] - rgb[2]) * rgb_illum_spect_yellow;
        r += (rgb[0] - rgb[1]) * rgb_illum_spect_red;
      }
    }
    r *= 0.86445;
  }
  return clamp(r);
}
specula::SampledSpectrum specula::SampledSpectrum::from_xyz(const Float xyz[3],
                                                            SpectrumType type) {
  Float rgb[3];
  xyz_to_rgb(xyz, rgb);
  return from_rgb(rgb, type);
}
specula::SampledSpectrum
specula::SampledSpectrum::from_sampled(const Float *lambda, const Float *v,
                                       std::size_t n) {
  if (!spectrum_samples_sorted(lambda, v, n)) {
    std::vector<Float> sorted_lambda(&lambda[0], &lambda[n]);
    std::vector<Float> sorted_v(&v[0], &v[n]);
    sort_spectrum_samples(&sorted_lambda[0], &sorted_v[0], n);
    return from_sampled(&sorted_lambda[0], &sorted_v[0], n);
  }
  SampledSpectrum r;
  for (std::size_t i = 0; i < spectral_samples; ++i) {
    Float lambda0 = lerp(Float(i) / Float(spectral_samples),
                         sampled_lambda_start, sampled_lambda_end);
    Float lambda1 = lerp(Float(i + 1) / Float(spectral_samples),
                         sampled_lambda_start, sampled_lambda_end);
    r.c[i] = average_spectrum_samples(lambda, v, n, lambda0, lambda1);
  }
  return r;
}

void specula::SampledSpectrum::init() {
  for (std::size_t i = 0; i < spectral_samples; ++i) {
    Float wl0 = lerp(Float(i) / Float(spectral_samples), sampled_lambda_start,
                     sampled_lambda_end);
    Float wl1 = lerp(Float(i + 1) / Float(spectral_samples),
                     sampled_lambda_start, sampled_lambda_end);

    X.c[i] = average_spectrum_samples(CIE_lambda, CIE_X, CIE_samples, wl0, wl1);
    Y.c[i] = average_spectrum_samples(CIE_lambda, CIE_Y, CIE_samples, wl0, wl1);
    Z.c[i] = average_spectrum_samples(CIE_lambda, CIE_Z, CIE_samples, wl0, wl1);

    rgb_refl_spect_white.c[i] = average_spectrum_samples(
        RGB_spect_lambda, RGB_refl_spect_white, RGB_spect_samples, wl0, wl1);
    rgb_refl_spect_cyan.c[i] = average_spectrum_samples(
        RGB_spect_lambda, RGB_refl_spect_cyan, RGB_spect_samples, wl0, wl1);
    rgb_refl_spect_magenta.c[i] = average_spectrum_samples(
        RGB_spect_lambda, RGB_refl_spect_magenta, RGB_spect_samples, wl0, wl1);
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
    rgb_illum_spect_magenta.c[i] = average_spectrum_samples(
        RGB_spect_lambda, RGB_illum_spect_magenta, RGB_spect_samples, wl0, wl1);
    rgb_illum_spect_yellow.c[i] = average_spectrum_samples(
        RGB_spect_lambda, RGB_illum_spect_yellow, RGB_spect_samples, wl0, wl1);
    rgb_illum_spect_red.c[i] = average_spectrum_samples(
        RGB_spect_lambda, RGB_illum_spect_red, RGB_spect_samples, wl0, wl1);
    rgb_illum_spect_green.c[i] = average_spectrum_samples(
        RGB_spect_lambda, RGB_illum_spect_green, RGB_spect_samples, wl0, wl1);
    rgb_illum_spect_blue.c[i] = average_spectrum_samples(
        RGB_spect_lambda, RGB_illum_spect_blue, RGB_spect_samples, wl0, wl1);
  }
}

specula::RGBSpectrum specula::SampledSpectrum::to_rgb_spectrum() const {
  Float rgb[3];
  to_rgb(rgb);
  return RGBSpectrum::from_rgb(rgb);
}
specula::SampledSpectrum specula::SampledSpectrum::to_sampled_spectrum() const {
  return *this;
}
