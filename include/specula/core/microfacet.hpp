#ifndef SPECULA_CORE_MICROFACET_HPP_
#define SPECULA_CORE_MICROFACET_HPP_

#include "geometry.hpp"
#include "specula/global.hpp"

namespace specula {
class MicrofacetDistribution {
public:
  virtual ~MicrofacetDistribution();

  virtual Float d(const Vector3f &wh) const = 0;
  virtual Float lambda(const Vector3f &w) const = 0;
  virtual Float g(const Vector3f &wo, const Vector3f &wi) const {
    return 1.0 / (1.0 + lambda(wo) + lambda(wi));
  }
  virtual Vector3f sample_wh(const Vector3f &wo, const Point2f &u) const = 0;

  Float g1(const Vector3f &w) const { return 1.0f / (1.0f + lambda(w)); }
  Float pdf(const Vector3f &wo, const Vector3f &wh) const;

  virtual std::string fmt() const = 0;

protected:
  MicrofacetDistribution(bool sample_visible_area)
      : sample_visible_area(sample_visible_area) {}
  const bool sample_visible_area;
};

class BeckmannDistribution : public MicrofacetDistribution {
public:
  BeckmannDistribution(Float alphax, Float alphay,
                       bool sample_visible_area = true)
      : MicrofacetDistribution(sample_visible_area), alphax(alphax),
        alphay(alphay) {}
  Float d(const Vector3f &wh) const;
  Vector3f sample_wh(const Vector3f &wo, const Point2f &u) const;

  std::string fmt() const;

private:
  Float lambda(const Vector3f &w) const;
  const Float alphax, alphay;
};

class TrowbridgeReitzDistribution : public MicrofacetDistribution {
public:
  TrowbridgeReitzDistribution(Float alphax, Float alphay,
                              bool sample_visible_area = true)
      : MicrofacetDistribution(sample_visible_area), alphax(alphax),
        alphay(alphay) {}

  Float d(const Vector3f &wh) const;
  Vector3f sample_wh(const Vector3f &wo, const Point2f &u) const;

  static inline Float roughness_to_alpha(Float roughness) {
    roughness = std::max(roughness, Float(1e-3));
    Float x = std::log(roughness);
    return 1.62142f + 0.819955f * x + 0.1734f * x * x + 0.0171201f * x * x * x +
           0.000640711f * x * x * x * x;
  }

  std::string fmt() const;

private:
  Float lambda(const Vector3f &w) const;
  const Float alphax, alphay;
};
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_MICROFACET_HPP_ */
