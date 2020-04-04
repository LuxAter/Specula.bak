#include "specula/core/sampling.hpp"

#include "global/constants.hpp"
#include "specula/core/geometry.hpp"
#include "specula/core/rng.hpp"
#include "specula/global.hpp"

specula::Distribution2D::Distribution2D(const Float *func, int nu, int nv) {
  conditional_val.reserve(nv);
  for (int v = 0; v < nv; ++v) {
    conditional_val.emplace_back(new Distribution1D(&func[v * nu], nu));
  }
  std::vector<Float> marginal_func;
  marginal_func.reserve(nv);
  for (int v = 0; v < nv; ++v)
    marginal_func.push_back(conditional_val[v]->func_int);
  marginal.reset(new Distribution1D(&marginal_func[0], nv));
}

void specula::stratified_sample(Float *samples, int n, Rng &rng, bool jitter) {
  Float inv_samples = Float(1) / n;
  for (int i = 0; i < n; ++i) {
    Float delta = jitter ? rng.uniform_float() : 0.5f;
    samples[i] = std::min((i + delta) * inv_samples, one_minus_epsilon);
  }
}
void specula::stratified_sample(Point2f *samples, int nx, int ny, Rng &rng,
                                bool jitter) {
  Float dx = Float(1) / nx, dy = Float(1) / ny;
  for (int y = 0; y < ny; ++y) {
    for (int x = 0; x < nx; ++x) {
      Float jx = jitter ? rng.uniform_float() : 0.5f;
      Float jy = jitter ? rng.uniform_float() : 0.5f;
      samples->x = std::min((x + jx) * dx, one_minus_epsilon);
      samples->y = std::min((y + jy) * dy, one_minus_epsilon);
      ++samples;
    }
  }
}
void specula::latin_hypercube(Float *samples, int n, int dim, Rng &rng) {
  Float inv_samples = Float(1) / n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < dim; ++j) {
      Float sj = (i + (rng.uniform_float())) * inv_samples;
      samples[dim * i + j] = std::min(sj, one_minus_epsilon);
    }
  }
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < n; ++j) {
      int other = j + rng.uniform_uint32(n - j);
      std::swap(samples[dim * j + i], samples[dim * other + i]);
    }
  }
}
specula::Point2f specula::rejection_sample_disk(Rng &rng) {
  Point2f p;
  do {
    p.x = 1 - 2 * rng.uniform_float();
    p.y = 1 - 2 * rng.uniform_float();
  } while (p.x * p.x + p.y * p.y > 1);
  return p;
}
specula::Vector3f specula::uniform_sample_hemisphere(const Point2f &u) {
  Float z = u[0];
  Float r = std::sqrt(std::max(Float(0), Float(1) - z * z));
  Float phi = 2 * PI * u[1];
  return Vector3f(r * std::cos(phi), r * std::sin(phi), z);
}
specula::Float specula::uniform_hemisphere_pdf() { return INV_2PI; }
specula::Vector3f specula::uniform_sample_sphere(const Point2f &u) {
  Float z = 1 - 2 * u[0];
  Float r = std::sqrt(std::max(Float(0), Float(1) - z * z));
  Float phi = 2 * PI * u[1];
  return Vector3f(r * std::cos(phi), r * std::sin(phi), z);
}
specula::Float specula::uniform_sphere_pdf() { return INV_4PI; }
specula::Vector3f specula::uniform_sample_cone(const Point2f &u,
                                               Float theta_max) {
  Float cos_theta = (Float(1) - u[0]) + u[0] * theta_max;
  Float sin_theta = std::sqrt(Float(1) - cos_theta * cos_theta);
  Float phi = u[1] * 2 * PI;
  return Vector3f(std::cos(phi) * sin_theta, std::sin(phi) * sin_theta,
                  cos_theta);
}
specula::Vector3f specula::uniform_sample_cone(const Point2f &u,
                                               Float theta_max,
                                               const Vector3f &x,
                                               const Vector3f &y,
                                               const Vector3f &z) {
  Float cos_theta = lerp(u[0], theta_max, 1.0f);
  Float sin_theta = std::sqrt(Float(1) - cos_theta * cos_theta);
  Float phi = u[1] * 2 * PI;
  return std::cos(phi) * sin_theta * x + std::sin(phi) * sin_theta * y +
         cos_theta * z;
}
specula::Float specula::uniform_cone_pdf(Float theta_max) {
  return 1 / (2 * PI * (1 - theta_max));
}
specula::Point2f specula::uniform_sample_disk(const Point2f &u) {
  Float r = std::sqrt(u[0]);
  Float theta = 2 * PI * u[1];
  return Point2f(r * std::cos(theta), r * std::sin(theta));
}
specula::Point2f specula::concentric_sample_disk(const Point2f &u) {
  Point2f offset = 2.0f * u - Vector2f(1, 1);
  if (offset.x == 0 && offset.y == 0)
    return Point2f(0, 0);
  Float theta, r;
  if (std::abs(offset.x) > std::abs(offset.y)) {
    r = offset.x;
    theta = PI_OVER4 * (offset.y / offset.x);
  } else {
    r = offset.y;
    theta = PI_OVER2 - PI_OVER4 * (offset.x / offset.y);
  }
  return r * Point2f(std::cos(theta), std::sin(theta));
}
specula::Point2f specula::uniform_sample_triangle(const Point2f &u) {
  Float su0 = std::sqrt(u[0]);
  return Point2f(1 - su0, u[1] * su0);
}
