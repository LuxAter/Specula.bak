#include "specula/core/spectrum/common.hpp"

bool specula::spectrum_samples_sorted(const Float *lambda, const Float *vals,
                                      std::size_t n) {
  for (std::size_t i = 0; i < n - 1; ++i)
    if (lambda[i] > lambda[i + 1])
      return false;
  return true;
}

void specula::sort_spectrum_samples(Float *lambda, Float *vals, std::size_t n) {
  std::vector<std::pair<Float, Float>> sort_vec;
  sort_vec.reserve(n);
  for (std::size_t i = 0; i < n; ++i)
    sort_vec.push_back(std::make_pair(lambda[i], vals[i]));
  std::sort(sort_vec.begin(), sort_vec.end());
  for (std::size_t i = 0; i < n; ++i) {
    lambda[i] = sort_vec[i].first;
    vals[i] = sort_vec[i].second;
  }
}

specula::Float specula::average_spectrum_samples(const Float *lambda, const Float *vals,
                               std::size_t n, Float lambda_start,
                               Float lambda_end){}

