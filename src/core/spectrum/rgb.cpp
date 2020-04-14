#include "specula/core/spectrum/rgb.hpp"
#include "specula/core/spectrum/sampled.hpp"

specula::SampledSpectrum specula::RGBSpectrum::to_sampled_spectrum() const {
  return SampledSpectrum::from_rgb(c);
}
