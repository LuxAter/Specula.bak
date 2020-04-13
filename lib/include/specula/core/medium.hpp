#ifndef SPECULA_CORE_MEDIUM_HPP_
#define SPECULA_CORE_MEDIUM_HPP_

#include "geometry.hpp"
#include "spectrum.hpp"
#include "specula/global.hpp"

namespace specula {
class PhaseFunction {
public:
  virtual ~PhaseFunction();
  virtual Float p(const Vector3f &wo, const Vector3f &wi) const = 0;
  virtual Float sample_p(const Vector3f &wo, Vector3f *wi,
                         const Point2f &u) const = 0;
  virtual std::string fmt() const = 0;
};

class HenyeyGreenstein : public PhaseFunction {
public:
  HenyeyGreenstein(Float g) : g(g) {}

  virtual Float p(const Vector3f &wo, const Vector3f &wi) const;
  virtual Float sample_p(const Vector3f &wo, Vector3f *wi,
                         const Point2f &u) const;
  virtual std::string fmt() const {
    return fmt::format("HenyeyGreenstein[g: {}]", g);
  }

private:
  const Float g;
};

class Medium {
public:
  virtual ~Medium() {}
  virtual Spectrum tr(const Ray &ray, Sampler &sampler) const = 0;
  virtual Spectrum sample(const Ray &ray, Sampler &sampler, MemoryArena &arena,
                          MediumInterface *mi) const = 0;
};

struct MediumInterface {
  MediumInterface() : inside(nullptr), outside(nullptr) {}
  MediumInterface(const Medium *medium) : inside(medium), outside(medium) {}
  MediumInterface(const Medium *inside, const Medium *outside)
      : inside(inside), outside(outside) {}

  bool is_medium_transition() const { return inside != outside; }

  const Medium *inside, *outside;
};

bool get_medium_scattering_properties(const std::string &name,
                                      Spectrum *sigma_a, Spectrum *sigma_s);

inline Float phase_hg(Float cos_theta, Float g) {
  Float denom = 1 + g * g + 2 * g * cos_theta;
  return INV_4PI * (1 - g * g) / (denom * std::sqrt(denom));
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const PhaseFunction &p) {
  return out << p.fmt();
}
} // namespace specula

#endif // SPECULA_CORE_MEDIUM_HPP_
