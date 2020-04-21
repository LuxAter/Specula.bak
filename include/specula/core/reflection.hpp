#ifndef SPECULA_CORE_REFLECTION_HPP_
#define SPECULA_CORE_REFLECTION_HPP_

#include "core/geometry/vector.hpp"
#include "core/interaction.hpp"
#include "core/microfacet.hpp"
#include "global/compiler.hpp"
#include "global/declarations.hpp"
#include "material.hpp"
#include "spectrum.hpp"
#include "specula/global.hpp"

namespace specula {

Float fr_dielectric(Float cos_thetaI, Float etaI, Float etaT);
Spectrum fr_conductor(Float cos_thetaI, const Spectrum &etaI,
                      const Spectrum &etaT, const Spectrum &k);

inline Float cos_theta(const Vector3f &w) { return w.z; }
inline Float cos2_theta(const Vector3f &w) { return w.z * w.z; }
inline Float abs_cos_theta(const Vector3f &w) { return std::abs(w.z); }
inline Float sin2_theta(const Vector3f &w) {
  return std::max(Float(0), Float(1) - cos2_theta(w));
}
inline Float sin_theta(const Vector3f &w) { return std::sqrt(sin2_theta(w)); }
inline Float tan_theta(const Vector3f &w) {
  return sin_theta(w) / cos_theta(w);
}
inline Float tan2_theta(const Vector3f &w) {
  return sin2_theta(w) / cos2_theta(w);
}
inline Float cos_phi(const Vector3f &w) {
  Float sint = sin_theta(w);
  return (sint == 0) ? 1 : clamp(w.x / sint, -1, 1);
}
inline Float sin_phi(const Vector3f &w) {
  Float sint = sin_theta(2);
  return (sint == 0) ? 0 : clamp(w.y / sint, -1, 1);
}
inline Float cos2_phi(const Vector3f &w) { return cos_phi(w) * cos_phi(w); }
inline Float sin2_phi(const Vector3f &w) { return sin_phi(w) * sin_phi(w); }
inline Float cosd_phi(const Vector3f &wa, const Vector3f &wb) {
  return clamp(
      (wa.x * wb.x + wa.y * wb.y) /
          std::sqrt((wa.x * wa.x + wa.y * wa.y) * (wb.x * wb.x + wb.y * wb.y)),
      -1, 1);
}
inline Vector3f reflect(const Vector3f &wo, const Vector3f &n) {
  return -wo + 2 * dot(wo, n) * n;
}
inline bool refract(const Vector3f &wi, const Normal3f &n, Float eta,
                    Vector3f *wt) {
  Float costI = dot(n, wi);
  Float sin2tI = std::max(Float(0), Float(1) - costI * costI);
  Float sin2tT = eta * eta * sin2tI;

  if (sin2tT >= 1)
    return false;
  Float costT = std::sqrt(1 - sin2tT);
  *wt = eta * -wi + (eta * costI - costT) * Vector3f(n);
  return true;
}
inline bool same_hemisphere(const Vector3f &w, const Vector3f &wp) {
  return w.z * wp.z > 0;
}
inline bool same_hemisphere(const Vector3f &w, const Normal3f &wp) {
  return w.z * wp.z > 0;
}

enum BxDFType {
  BSDF_REFLECTION = 1 << 0,
  BSDF_TRANSMISSION = 1 << 1,
  BSDF_DIFFUSE = 1 << 2,
  BSDF_GLOSSY = 1 << 3,
  BSDF_SPECULAR = 1 << 4,
  BSDF_ALL = BSDF_DIFFUSE | BSDF_REFLECTION | BSDF_GLOSSY | BSDF_SPECULAR |
             BSDF_TRANSMISSION,
};

struct FourierBSDFTable {
  static bool read(const std::string &filename, FourierBSDFTable *table);
  const Float *get_ak(int offsetI, int offsetO, int *mptr) const {
    *mptr = m[offsetO * nmu + offsetI];
    return a + aoffset[offsetO * nmu + offsetI];
  }
  bool get_weights_and_offset(Float cost, int *offset, Float weights[4]) const;
  Float eta;
  int mmax;
  int nchannels;
  int nmu;
  Float *mu;
  int *m;
  int *aoffset;
  Float *a;
  Float *a0;
  Float *cdf;
  Float *recip;
};

class BSDF {
public:
  BSDF(const SurfaceInteraction &si, Float eta = 1)
      : eta(eta), ns(si.shading.n), ng(si.n), ss(normalize(si.shading.dpdu)),
        ts(cross(ns, ss)) {}

  void add(BxDF *b) {
    CHECK_LT(nBxDFs, max_BxDFs);
    bxdfs[nBxDFs++] = b;
  }
  int num_components(BxDFType flags = BSDF_ALL) const;
  Vector3f world_to_local(const Vector3f &v) const {
    return Vector3f(dot(v, ss), dot(v, ts), dot(v, ns));
  }
  Vector3f local_to_world(const Vector3f &v) const {
    return Vector3f(ss.x * v.x + ts.x * v.y + ns.x * v.z,
                    ss.y * v.x + ts.y * v.y + ns.y * v.z,
                    ss.z * v.x + ts.z * v.y + ns.z * v.z);
  }
  Spectrum f(const Vector3f &wow, const Vector3f &wiw,
             BxDFType flags = BSDF_ALL) const;
  Spectrum rho(int nSamples, const Point2f *samples1, const Point2f *samples2,
               BxDFType flags = BSDF_ALL) const;
  Spectrum rho(const Vector3f &wo, int nSamples, const Point2f *samples,
               BxDFType flags = BSDF_ALL) const;
  Spectrum sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &u,
                    Float *pdf, BxDFType type = BSDF_ALL,
                    BxDFType *sampled_type = nullptr) const;

  Float pdf(const Vector3f &wo, const Vector3f &wi,
            BxDFType flags = BSDF_ALL) const;

  std::string fmt() const;

  const Float eta;

private:
  ~BSDF() {}

  const Normal3f ns, ng;
  const Vector3f ss, ts;
  int nBxDFs = 0;
  static SPECULA_CONSTEXPR int max_BxDFs = 8;
  BxDF *bxdfs[max_BxDFs];
  friend class MixMaterial;
};

class BxDF {
public:
  BxDF(BxDFType type) : type(type) {}
  virtual ~BxDF() {}

  bool matches_flags(BxDFType t) const { return (type & t) == type; }

  virtual Spectrum f(const Vector3f &wo, const Vector3f &wi) const = 0;
  virtual Spectrum rho(int nsamples, const Point2f *samples1,
                       const Point2f *samples2) const;
  virtual Spectrum rho(const Vector3f &wo, int nSamples,
                       const Point2f *samples) const;
  virtual Spectrum sample_f(const Vector3f &wo, Vector3f *wi,
                            const Point2f &sample, Float *pdf,
                            BxDFType *sampled_type = nullptr) const;

  virtual Float pdf(const Vector3f &wo, const Vector3f &wi) const;

  virtual std::string fmt() const = 0;

  const BxDFType type;
};

class ScaledBxDF : public BxDF {
public:
  ScaledBxDF(BxDF *bxdf, const Spectrum &scale)
      : BxDF(BxDFType(bxdf->type)), bxdf(bxdf), scale(scale) {}

  Spectrum f(const Vector3f &wo, const Vector3f &wi) const;
  Spectrum rho(int nsamples, const Point2f *samples1,
               const Point2f *samples2) const {
    return scale * bxdf->rho(nsamples, samples1, samples2);
  }
  Spectrum rho(const Vector3f &wo, int nsamples, const Point2f *samples) const {
    return scale * bxdf->rho(wo, nsamples, samples);
  }
  Spectrum sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &sample,
                    Float *pdf, BxDFType *sampled_type = nullptr) const;
  Float pdf(const Vector3f &wo, const Vector3f &wi) const;

  std::string fmt() const;

private:
  BxDF *bxdf;
  Spectrum scale;
};

class Fresnel {
public:
  virtual ~Fresnel();
  virtual Spectrum evaluate(Float cosi) const = 0;

  virtual std::string fmt() const = 0;
};

class FresnelConductor : public Fresnel {
public:
  FresnelConductor(const Spectrum &etai, const Spectrum &etat,
                   const Spectrum &k)
      : etai(etai), etat(etat), k(k) {}

  Spectrum evaluate(Float cosi) const;

  std::string fmt() const;

private:
  Spectrum etai, etat, k;
};

class FresnelDielectric : public Fresnel {
public:
  FresnelDielectric(Float etai, Float etat) : etai(etai), etat(etat) {}

  Spectrum evaluate(Float cosi) const;

  std::string fmt() const;

private:
  Float etai, etat;
};

class FresnelNoOp : public Fresnel {
public:
  Spectrum evaluate(Float) const { return Spectrum(1.0f); }
  std::string fmt() const { return "[FresnelNoOp]"; }
};

class SpecularReflection : public BxDF {
public:
  SpecularReflection(const Spectrum &r, Fresnel *fresnel)
      : BxDF(BxDFType(BSDF_REFLECTION | BSDF_SPECULAR)), r(r),
        fresnel(fresnel) {}

  Spectrum f(const Vector3f &wo, const Vector3f &wi) const {
    return Spectrum(0.0f);
  }
  Spectrum sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &sample,
                    Float *pdf, BxDFType *sampled_type) const;

  Float pdf(const Vector3f &wo, const Vector3f &wi) const { return 0; }

  std::string fmt() const;

private:
  const Spectrum r;
  const Fresnel *fresnel;
};

class SpecularTransmission : public BxDF {
public:
  SpecularTransmission(const Spectrum &t, Float etaa, Float etab,
                       TransportMode mode)
      : BxDF(BxDFType(BSDF_TRANSMISSION | BSDF_SPECULAR)), t(t), etaa(etaa),
        etab(etab), fresnel(etaa, etab), mode(mode) {}

  Spectrum f(const Vector3f &wo, const Vector3f &wi) const {
    return Spectrum(0.0f);
  }
  Spectrum sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &sample,
                    Float *pdf, BxDFType *sampled_type) const;

  Float pdf(const Vector3f &wo, const Vector3f &wi) const { return 0; }

  std::string fmt() const;

private:
  const Spectrum t;
  const Float etaa, etab;
  const FresnelDielectric fresnel;
  const TransportMode mode;
};

class FresnelSpecular : public BxDF {
public:
  FresnelSpecular(const Spectrum &r, const Spectrum &t, Float etaa, Float etab,
                  TransportMode mode)
      : BxDF(BxDFType(BSDF_REFLECTION | BSDF_TRANSMISSION | BSDF_SPECULAR)),
        r(r), t(t), etaa(etaa), etab(etab), mode(mode) {}

  Spectrum f(const Vector3f &wo, const Vector3f &wi) const {
    return Spectrum(0.0f);
  }
  Spectrum sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &sample,
                    Float *pdf, BxDFType *sampled_type) const;

  Float pdf(const Vector3f &wo, const Vector3f &wi) const { return 0; }

  std::string fmt() const;

private:
  const Spectrum r, t;
  const Float etaa, etab;
  const TransportMode mode;
};

class LambertianReflection : public BxDF {
public:
  LambertianReflection(const Spectrum &r)
      : BxDF(BxDFType(BSDF_REFLECTION | BSDF_DIFFUSE)), r(r) {}

  Spectrum f(const Vector3f &wo, const Vector3f &wi) const;
  Spectrum rho(int nsamples, const Point3f *samples1,
               const Point2f *samples2) const {
    return r;
  }
  Spectrum rho(const Vector3f &wo, int nSamples, const Point3f *samples) const {
    return r;
  }

  std::string fmt() const;

private:
  const Spectrum r;
};
class LambertianTransmission : public BxDF {
public:
  LambertianTransmission(const Spectrum &t)
      : BxDF(BxDFType(BSDF_TRANSMISSION | BSDF_DIFFUSE)), t(t) {}

  Spectrum f(const Vector3f &wo, const Vector3f &wi) const;
  Spectrum rho(int nsamples, const Point3f *samples1,
               const Point2f *samples2) const {
    return t;
  }
  Spectrum rho(const Vector3f &wo, int nSamples, const Point3f *samples) const {
    return t;
  }
  Spectrum sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &sample,
                    Float *pdf, BxDFType *sampled_type) const;

  Float pdf(const Vector3f &wo, const Vector3f &wi) const;

  std::string fmt() const;

private:
  const Spectrum t;
};

class OrenNayar : public BxDF {
public:
  OrenNayar(const Spectrum &r, Float sigma)
      : BxDF(BxDFType(BSDF_REFLECTION | BSDF_DIFFUSE)), r(r) {
    sigma = radians(sigma);
    Float sigma2 = sigma * sigma;
    a = 1.0f - (sigma2 / (2.0f * (sigma2 + 0.33f)));
    b = 0.45f * sigma2 / (sigma2 + 0.09f);
  }

  Spectrum f(const Vector3f &wo, const Vector3f &wi) const;

  std::string fmt() const;

private:
  const Spectrum r;
  Float a, b;
};

class MicrofacetTransmission : public BxDF {
public:
  MicrofacetTransmission(const Spectrum &t,
                         MicrofacetDistribution *distribution, Float etaa,
                         Float etab, TransportMode mode)
      : BxDF(BxDFType(BSDF_TRANSMISSION | BSDF_GLOSSY)), t(t),
        distribution(distribution), etaa(etaa), etab(etab), fresnel(etaa, etab),
        mode(mode) {}

  Spectrum f(const Vector3f &wo, const Vector3f &wi) const;
  Spectrum sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &u,
                    Float *pdf, BxDFType *sampled_type) const;

  Float pdf(const Vector3f &wo, const Vector3f &wi) const;

  std::string fmt() const;

private:
  const Spectrum t;
  const MicrofacetDistribution *distribution;
  const Float etaa, etab;
  const FresnelDielectric fresnel;
  const TransportMode mode;
};

class MicrofacetReflection : public BxDF {
public:
  MicrofacetReflection(const Spectrum &r, MicrofacetDistribution *distribution,
                       Fresnel *fresnel)
      : BxDF(BxDFType(BSDF_REFLECTION | BSDF_GLOSSY)), r(r),
        distribution(distribution), fresnel(fresnel) {}

  Spectrum f(const Vector3f &wo, const Vector3f &wi) const;
  Spectrum sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &u,
                    Float *pdf, BxDFType *sampled_type) const;

  Float pdf(const Vector3f &wo, const Vector3f &wi) const;

  std::string fmt() const;

private:
  const Spectrum r;
  const MicrofacetDistribution *distribution;
  const Fresnel *fresnel;
};

class FresnelBlend : public BxDF {
public:
  FresnelBlend(const Spectrum &rd, const Spectrum &rs,
               MicrofacetDistribution *distribution);

  Spectrum f(const Vector3f &wo, const Vector3f &wi) const;
  Spectrum sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &u,
                    Float *pdf, BxDFType *sampled_type) const;

  Spectrum schlick_fresnel(Float cos_theta_i) const {
    auto pow5 = [](Float v) { return (v * v) * (v * v) * v; };
    return rs + pow5(1 - cos_theta_i) * (Spectrum(1.0f) - rs);
  }

  Float pdf(const Vector3f &wo, const Vector3f &wi) const;

  std::string fmt() const;

private:
  const Spectrum rd, rs;
  MicrofacetDistribution *distribution;
};

class FourierBSDF : public BxDF {
public:
  FourierBSDF(const FourierBSDFTable &bsdf_table, TransportMode mode)
      : BxDF(BxDFType(BSDF_REFLECTION | BSDF_TRANSMISSION | BSDF_GLOSSY)),
        bsdf_table(bsdf_table), mode(mode) {}

  Spectrum f(const Vector3f &wo, const Vector3f &wi) const;
  Spectrum sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &u,
                    Float *pdf, BxDFType *sampled_type) const;

  Float pdf(const Vector3f &wo, const Vector3f &wi) const;

  std::string fmt() const;

private:
  const FourierBSDFTable &bsdf_table;
  const TransportMode mode;
};

} // namespace specula

inline int specula::BSDF::num_components(BxDFType flags) const {
  int num = 0;
  for (int i = 0; i < nBxDFs; ++i) {
    if (bxdfs[i]->matches_flags(flags))
      ++num;
  }
  return num;
}

#endif // SPECULA_CORE_REFLECTION_HPP_
