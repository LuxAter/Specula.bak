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

specula::Float specula::average_spectrum_samples(const Float *lambda,
                                                 const Float *vals,
                                                 std::size_t n,
                                                 Float lambda_start,
                                                 Float lambda_end) {
  for (std::size_t i = 0; i < n - 1; ++i)
    CHECK_GT(lambda[i + 1], lambda[i]);
  CHECK_LT(lambda_start, lambda_end);
  if (lambda_end <= lambda[0])
    return vals[0];
  else if (lambda_start >= lambda[n - 1])
    return vals[n - 1];
  else if (n == 1)
    return vals[0];
  Float sum = 0;
  if (lambda_start < lambda[0])
    sum += vals[0] * (lambda[0] - lambda_start);
  if (lambda_end > lambda[n - 1])
    sum += vals[n - 1] * (lambda_end - lambda[n - 1]);

  std::size_t i = 0;
  while (lambda_start > lambda[i + 1])
    ++i;
  CHECK_LT(i + 1, n);
  auto interp = [lambda, vals](Float w, std::size_t i) {
    return lerp((w - lambda[i]) / (lambda[i + 1] - lambda[i]), vals[i],
                vals[i + 1]);
  };
  for (; i + 1 < n && lambda_end >= lambda[i]; ++i) {
    Float seg_lambda_start = std::max(lambda_start, lambda[i]);
    Float seg_lambda_end = std::min(lambda_end, lambda[i + 1]);
    sum += 0.5 * (interp(seg_lambda_start, i) + interp(seg_lambda_end, i)) *
           (seg_lambda_end - seg_lambda_start);
  }
  return sum / (lambda_end - lambda_start);
}
