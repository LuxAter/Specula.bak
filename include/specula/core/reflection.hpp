#ifndef SPECULA_CORE_REFLECTION_HPP_
#define SPECULA_CORE_REFLECTION_HPP_

#include "core/geometry/vector.hpp"
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

} // namespace specula

#endif // SPECULA_CORE_REFLECTION_HPP_
