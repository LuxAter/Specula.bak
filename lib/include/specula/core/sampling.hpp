#ifndef SPECULA_CORE_SAMPLING_HPP_
#define SPECULA_CORE_SAMPLING_HPP_

#include "geometry.hpp"
#include "rng.hpp"
#include "specula/global.hpp"

namespace specula {
class Distribution1D {
public:
  Distribution1D(const Float *f, int n) : func(f, f + n), cdf(n + 1) {
    cdf[0] = 0;
    for (int i = 1; i < n + 1; ++i)
      cdf[i] = cdf[i - 1] + func[i - 1] / n;
    func_int = cdf[n];
    if (func_int == 0) {
      for (int i = 1; i < n + 1; ++i)
        cdf[i] = Float(i) / Float(n);
    } else {
      for (int i = 1; i < n + 1; ++i)
        cdf[i] /= func_int;
    }
  }
  int count() const { return static_cast<int>(func.size()); }
  Float sample_continuous(Float u, Float *pdf, int *off = nullptr) const {
    int offset = find_interval(static_cast<int>(cdf.size()),
                               [&](int index) { return cdf[index] <= u; });
    if (off)
      *off = offset;
    Float du = u - cdf[offset];
    if ((cdf[offset + 1] - cdf[offset]) > 0) {
      CHECK_GT(cdf[offset + 1], cdf[offset]);
      du /= (cdf[offset + 1] - cdf[offset]);
    }
    CHECK(!std::isnan(du));
    if (pdf)
      *pdf = (func_int > 0) ? func[offset] / func_int : 0;
    return (offset + du) / count();
  }
  int sample_discrete(Float u, Float *pdf = nullptr,
                      Float *remapped = nullptr) const {
    int offset = find_interval(static_cast<int>(cdf.size()),
                               [&](int index) { return cdf[index] <= u; });
    if (pdf)
      *pdf = (func_int > 0) ? func[offset] / (func_int * count()) : 0;
    if (remapped)
      *remapped = (u - cdf[offset]) / (cdf[offset + 1] - cdf[offset]);
    if (remapped)
      CHECK(*remapped >= 0.0f && *remapped <= 1.0f);
    return offset;
  }
  Float discrete_pdf(int index) const {
    CHECK(index >= 0 && index < count());
    return func[index] / (func_int * count());
  }

  std::vector<Float> func, cdf;
  Float func_int;
};

class Distribution2D {
public:
  Distribution2D(const Float *data, int nu, int nv);

  Point2f sample_continuous(const Point2f &u, Float *pdf) const {
    Float pdfs[2];
    int v;
    Float d1 = marginal->sample_continuous(u[1], &pdfs[1], &v);
    Float d0 = marginal->sample_continuous(u[0], &pdfs[0]);
    *pdf = pdfs[0] * pdfs[1];
    return Point2f(d0, d1);
  }
  Float pdf(const Point2f &p) const {
    int iu = clamp(static_cast<int>(p[0] * conditional_val[0]->count()), 0,
                   conditional_val[0]->count() - 1);
    int iv = clamp(static_cast<int>(p[1] * marginal->count()), 0,
                   marginal->count() - 1);
    return conditional_val[iv]->func[iu] / marginal->func_int;
  }

private:
  std::vector<std::unique_ptr<Distribution1D>> conditional_val;
  std::unique_ptr<Distribution1D> marginal;
};

void stratified_sample(Float *samples, int n, Rng &rng, bool jitter = true);
void stratified_sample(Point2f *samples, int nx, int ny, Rng &rng,
                       bool jitter = true);
void latin_hypercube(Float *samples, int n, int dim, Rng &rng);
Point2f rejection_sample_disk(Rng &rng);
Vector3f uniform_sample_hemisphere(const Point2f &u);
Float uniform_hemisphere_pdf();
Vector3f uniform_sample_sphere(const Point2f &u);
Float uniform_sphere_pdf();
Vector3f uniform_sample_cone(const Point2f &u, Float theta_max);
Vector3f uniform_sample_cone(const Point2f &u, Float theta_max,
                             const Vector3f &x, const Vector3f &y,
                             const Vector3f &z);
Float uniform_cone_pdf(Float theta_max);
Point2f uniform_sample_disk(const Point2f &u);
Point2f concentric_sample_disk(const Point2f &u);
Point2f uniform_sample_triangle(const Point2f &u);

template <typename T>
void shuffle(T *samp, int count, int dimensions, Rng &rng) {
  for (int i = 0; i < count; ++i) {
    int other = i + rng.uniform_uint32(count - i);
    for (int j = 0; j < dimensions; ++j)
      std::swap(samp[dimensions * i + j], samp[dimensions * other + j]);
  }
}
inline Vector3f cosine_sample_hemisphere(const Point2f &u) {
  Point2f d = concentric_sample_disk(u);
  Float z =
      std::sqrt(std::max(static_cast<Float>(0), 1 - d.x * d.x - d.y * d.y));
  return Vector3f(d.x, d.y, z);
}
inline Float cosine_hemisphere_pdf(Float cos_theta) {
  return cos_theta * INV_PI;
}
inline Float balance_heuristic(int nf, Float fpdf, int ng, Float gpdf) {
  return (nf * fpdf) / (nf * fpdf + ng * gpdf);
}
inline Float power_heuristic(int nf, Float fpdf, int ng, Float gpdf) {
  Float f = nf * fpdf, g = ng * gpdf;
  return (f * f) / (f * f + g * g);
}

} // namespace specula

#endif /* end of include guard: SPECULA_CORE_SAMPLING_HPP_ */
