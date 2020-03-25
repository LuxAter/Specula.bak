#ifndef SPECULA_CORE_SPECTRUM_COMMON_HPP_
#define SPECULA_CORE_SPECTRUM_COMMON_HPP_

#include "specula/global.hpp"

namespace specula {
bool spectrum_samples_sorted(const Float *lambda, const Float *vals,
                             std::size_t n);
void sort_spectrum_samples(Float *lambda, Float *vals, std::size_t n);
Float average_spectrum_samples(const Float *lambda, const Float *vals,
                               std::size_t n, Float lambda_start,
                               Float lambda_end);

inline void xyz_to_rgb(const Float xyz[3], Float rgb[3]) {}
inline void rgb_to_xyz(const Float rgb[3], Float xyz[3]) {}
Float interpolate_spectrum_samples(const Float *lambda, const Float *vals,
                                   std::size_t n, Float l);
void blackbody(const Float *lambda, std::size_t n, Float T, Float *Le);
void blackbody_normalized(const Float *lambda, std::size_t n, Float T,
                          Float *vals);

static const std::size_t sampled_lambda_start = 400;
static const std::size_t sampled_lambda_end = 700;
static const std::size_t spectral_samples = 60;
static const std::size_t CIE_samples = 471;
static const std::size_t RGB_spect_samples = 32;
static const Float CIE_Y_integral = 106.856895;
extern const Float CIE_X[CIE_samples];
extern const Float CIE_Y[CIE_samples];
extern const Float CIE_Z[CIE_samples];
extern const Float CIE_lambda[CIE_samples];
extern const Float RGB_spect_lambda[RGB_spect_samples];
extern const Float RGB_refl_spect_white[RGB_spect_samples];
extern const Float RGB_refl_spect_cyan[RGB_spect_samples];
extern const Float RGB_refl_spect_magenta[RGB_spect_samples];
extern const Float RGB_refl_spect_yellow[RGB_spect_samples];
extern const Float RGB_refl_spect_red[RGB_spect_samples];
extern const Float RGB_refl_spect_green[RGB_spect_samples];
extern const Float RGB_refl_spect_blue[RGB_spect_samples];
extern const Float RGB_illum_spect_white[RGB_spect_samples];
extern const Float RGB_illum_spect_cyan[RGB_spect_samples];
extern const Float RGB_illum_spect_magenta[RGB_spect_samples];
extern const Float RGB_illum_spect_yellow[RGB_spect_samples];
extern const Float RGB_illum_spect_red[RGB_spect_samples];
extern const Float RGB_illum_spect_green[RGB_spect_samples];
extern const Float RGB_illum_spect_blue[RGB_spect_samples];
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_SPECTRUM_COMMON_HPP_ */
