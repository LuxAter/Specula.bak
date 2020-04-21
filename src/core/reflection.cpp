#include "specula/core/reflection.hpp"
#include "core/geometry/common.hpp"
#include "core/material.hpp"
#include "core/microfacet.hpp"
#include "core/rng.hpp"
#include "core/sampling.hpp"
#include "global/declarations.hpp"

namespace specula {
Float fr_dielectric(Float cos_thetai, Float etai, Float etat) {
  cos_thetai = clamp(cos_thetai, -1, 1);
  bool entering = cos_thetai > 0.0f;
  if (!entering) {
    std::swap(etai, etat);
    cos_thetai = std::abs(cos_thetai);
  }
  Float sin_thetai = std::sqrt(std::max(Float(0), 1 - cos_thetai * cos_thetai));
  Float sin_thetat = etai / etat * sin_thetai;

  if (sin_thetat > 1)
    return 1;
  Float cos_thetat = std::sqrt(std::max(Float(0), 1 - sin_thetat * sin_thetat));
  Float rparl = ((etat * cos_thetai) - (etai * cos_thetat)) /
                ((etat * cos_thetai) + (etai * cos_thetat));

  Float rperp = ((etai * cos_thetai) - (etat * cos_thetat)) /
                ((etai * cos_thetai) + (etat * cos_thetat));
  return (rparl * rparl + rperp * rperp) / 2;
}

Spectrum fr_conductor(Float cos_thetai, const Spectrum &etai,
                      const Spectrum &etat, const Spectrum &k) {
  cos_thetai = clamp(cos_thetai, -1, 1);
  Spectrum eta = etat / etai;
  Spectrum etak = k / etai;

  Float cos_thetai2 = cos_thetai * cos_thetai;
  Float sin_thetai2 = 1.0 - cos_thetai2;
  Spectrum eta2 = eta * eta;
  Spectrum etak2 = etak * etak;

  Spectrum t0 = eta2 - etak2 - sin_thetai2;
  Spectrum a2plusb2 = sqrt(t0 * t0 + 4 * eta2 * etak2);
  Spectrum t1 = a2plusb2 + cos_thetai2;
  Spectrum a = sqrt(0.5f * (a2plusb2 + t0));
  Spectrum t2 = Float(2) * cos_thetai * a;
  Spectrum rs = (t1 - t2) / (t1 + t2);

  Spectrum t3 = cos_thetai2 * a2plusb2 + sin_thetai2 * sin_thetai2;
  Spectrum t4 = t2 * sin_thetai2;
  Spectrum rp = rs * (t3 - t4) / (t3 + t4);
  return 0.5 * (rp + rs);
}
} // namespace specula

specula::Spectrum specula::ScaledBxDF::f(const Vector3f &wo,
                                         const Vector3f &wi) const {
  return scale * bxdf->f(wo, wi);
}
specula::Spectrum specula::ScaledBxDF::sample_f(const Vector3f &wo,
                                                Vector3f *wi,
                                                const Point2f &sample,
                                                Float *pdf,
                                                BxDFType *sampled_type) const {
  Spectrum f = bxdf->sample_f(wo, wi, sample, pdf, sampled_type);
  return scale * f;
}
specula::Float specula::ScaledBxDF::pdf(const Vector3f &wo,
                                        const Vector3f &wi) const {
  return bxdf->pdf(wo, wi);
}

std::string specula::ScaledBxDF::fmt() const {
  return fmt::format("<BxDF.ScaledBxDF bxdf: {} scale: {}>", bxdf->fmt(),
                     scale);
}

specula::Fresnel::~Fresnel() {}
specula::Spectrum specula::FresnelConductor::evaluate(Float cos_thetai) const {
  return fr_conductor(std::abs(cos_thetai), etai, etat, k);
}
std::string specula::FresnelConductor::fmt() const {
  return fmt::format("<Fresnel.FresnelConductor etaI: {} etaT: {} k: {}>", etai,
                     etat, k);
}

specula::Spectrum specula::FresnelDielectric::evaluate(Float cos_thetai) const {
  return fr_dielectric(cos_thetai, etai, etat);
}
std::string specula::FresnelDielectric::fmt() const {
  return fmt::format("<Fresnel.Fre etaI: {} etaT: {}>", etai, etat);
}

specula::Spectrum
specula::SpecularReflection::sample_f(const Vector3f &wo, Vector3f *wi,
                                      const Point2f &sample, Float *pdf,
                                      BxDFType *sampled_type) const {
  *wi = Vector3f(-wo.x, -wo.y, wo.z);
  *pdf = 1;
  return fresnel->evaluate(cos_theta(*wi)) * r / abs_cos_theta(*wi);
}
std::string specula::SpecularReflection::fmt() const {
  return fmt::format("<BxDF.SpecularReflection R: {} fresnel: {}>", r,
                     fresnel->fmt());
}
specula::Spectrum
specula::SpecularTransmission::sample_f(const Vector3f &wo, Vector3f *wi,
                                        const Point2f &sample, Float *pdf,
                                        BxDFType *sampled_type) const {
  bool entering = cos_theta(wo) > 0;
  Float etai = entering ? etaa : etab;
  Float etat = entering ? etab : etaa;

  if (!refract(wo, faceforward(Normal3f(0, 0, 1), wo), etai / etat, wi))
    return 0;
  *pdf = 1;
  Spectrum ft = t * (Spectrum(1.0) - fresnel.evaluate(cos_theta(*wi)));
  return ft / abs_cos_theta(*wi);
}
std::string specula::SpecularTransmission::fmt() const {
  return fmt::format(
      "<BxDF.SpecularTransmission T: {} etaA: {} etaB: {} fresnel: {} mode: "
      "{}>",
      t, etaa, etab, fresnel.fmt(),
      (mode == TransportMode::RADIANCE ? "RADIANCE" : "IMPORTANCE"));
}

specula::Spectrum specula::LambertianReflection::f(const Vector3f &wo,
                                                   const Vector3f &wi) const {
  return r * INV_PI;
}
std::string specula::LambertianReflection::fmt() const {
  return fmt::format("<BxDF.LambertianReflection R:{}>", r.fmt());
}
specula::Spectrum specula::LambertianTransmission::f(const Vector3f &wo,
                                                     const Vector3f &wi) const {
  return t * INV_PI;
}
std::string specula::LambertianTransmission::fmt() const {
  return fmt::format("<BxDF.LambertianTransmission T:{}>", t.fmt());
}
specula::Spectrum specula::OrenNayar::f(const Vector3f &wo,
                                        const Vector3f &wi) const {
  Float sin_thetai = sin_theta(wi);
  Float sin_thetao = sin_theta(wo);

  Float max_cos = 0;
  if (sin_thetai > 1e-4 && sin_thetao > 1e-4) {
    Float sin_phii = sin_phi(wi), cos_phii = cos_phi(wi);
    Float sin_phio = sin_phi(wo), cos_phio = cos_phi(wo);
    Float dcos = cos_phii * cos_phio + sin_phii * sin_phio;
    max_cos = std::max(Float(0), dcos);
  }

  Float sin_alpha, tan_beta;
  if (abs_cos_theta(wi) > abs_cos_theta(wo)) {
    sin_alpha = sin_thetao;
    tan_beta = sin_thetai / abs_cos_theta(wi);
  } else {
    sin_alpha = sin_thetai;
    tan_beta = sin_thetao / abs_cos_theta(wo);
  }
  return r * INV_PI * (a + b * max_cos * sin_alpha * tan_beta);
}
std::string specula::OrenNayar::fmt() const {
  return fmt::format("<Bxdf.OrenNayar R: {} A: {} B: {}>", r.fmt(), a, b);
}
specula::Spectrum specula::MicrofacetReflection::f(const Vector3f &wo,
                                                   const Vector3f &wi) const {
  Float cos_thetao = abs_cos_theta(wo), cos_thetai = abs_cos_theta(wi);
  Vector3f wh = wi + wo;
  if (cos_thetai == 0 || cos_thetao == 0)
    return Spectrum(0.0f);
  else if (wh.x == 0 && wh.y == 0 && wh.z == 0)
    return Spectrum(0.0f);
  wh = normalize(wh);
  Spectrum f = fresnel->evaluate(dot(wi, faceforward(wh, Vector3f(0, 0, 1))));
  return r * distribution->d(wh) * distribution->g(wo, wi) * f /
         (4 * cos_thetai * cos_thetao);
}
std::string specula::MicrofacetReflection::fmt() const {
  return fmt::format(
      "<Bxdf.MicrofacetReflection R: {} distribution: {} fresnel: {}>", r.fmt(),
      distribution->fmt(), fresnel->fmt());
}
specula::Spectrum specula::MicrofacetTransmission::f(const Vector3f &wo,
                                                     const Vector3f &wi) const {
  if (same_hemisphere(wo, wi))
    return 0;
  Float cos_thetao = cos_theta(wo);
  Float cos_thetai = cos_theta(wi);
  if (cos_thetai == 0 || cos_thetao == 0)
    return Spectrum(0.0f);

  Float eta = cos_theta(wo) > 0 ? (etab / etaa) : (etaa / etab);
  Vector3f wh = normalize(wo + wi * eta);
  if (wh.z < 0)
    wh = -wh;

  Spectrum f = fresnel.evaluate(dot(wo, wh));

  Float sqrt_denom = dot(wo, wh) + eta * dot(wi, wh);
  Float factor = (mode == TransportMode::RADIANCE) ? (1 / eta) : 1;

  return (Spectrum(1.0f) - f) * t *
         std::abs(distribution->d(wh) * distribution->g(wo, wi) * eta * eta *
                  abs_dot(wi, wh) * abs_dot(wo, wh) * factor * factor /
                  (cos_thetai * cos_thetao * sqrt_denom * sqrt_denom));
}
std::string specula::MicrofacetTransmission::fmt() const {
  return fmt::format(
      "<Bxdf.MicrofacetTransmission T: {} distribution: {} etaA: {} etaB: {} "
      "fresnel: {} mode: {}>",
      t.fmt(), distribution->fmt(), etaa, etab, fresnel.fmt(),
      (mode == TransportMode::RADIANCE ? "RADIANCE" : "IMPORTANCE"));
}

specula::FresnelBlend::FresnelBlend(const Spectrum &rd, const Spectrum &rs,
                                    MicrofacetDistribution *distribution)
    : BxDF(BxDFType(BSDF_REFLECTION | BSDF_GLOSSY)), rd(rd), rs(rs),
      distribution(distribution) {}
specula::Spectrum specula::FresnelBlend::f(const Vector3f &wo,
                                           const Vector3f &wi) const {
  auto pow5 = [](Float v) { return (v * v) * (v * v) * v; };
  Spectrum diffuse = (28.0f / (23.0f * PI)) * rd * (Spectrum(1.0f) - rs) *
                     (1 - pow5(1 - 0.5f * abs_cos_theta(wi))) *
                     (1 - pow5(1 - 0.5f * abs_cos_theta(wo)));
  Vector3f wh = wi + wo;
  if (wh.x == 0 && wh.y == 0 && wh.z == 0)
    return Spectrum(0);
  wh = normalize(wh);
  Spectrum specular =
      distribution->d(wh) /
      (4 * abs_dot(wi, wh) * std::max(abs_cos_theta(wi), abs_cos_theta(wo))) *
      schlick_fresnel(dot(wi, wh));
  return diffuse + specular;
}
std::string specula::FresnelBlend::fmt() const {
  return fmt::format("<BxDF.FresnelBlend Rd: {} Rs: {} distribution: {}>",
                     rd.fmt(), rs.fmt(), distribution->fmt());
}

specula::Spectrum specula::BxDF::sample_f(const Vector3f &wo, Vector3f *wi,
                                          const Point2f &sample, Float *p,
                                          BxDFType *sampled_type) const {
  *wi = cosine_sample_hemisphere(sample);
  if (wo.z < 0)
    wi->z *= -1;
  *p = pdf(wo, *wi);
  return f(wo, *wi);
}
specula::Float specula::BxDF::pdf(const Vector3f &wo,
                                  const Vector3f &wi) const {
  return same_hemisphere(wo, wi) ? abs_cos_theta(wi) * INV_PI : 0;
}

specula::Spectrum
specula::LambertianTransmission::sample_f(const Vector3f &wo, Vector3f *wi,
                                          const Point2f &sample, Float *p,
                                          BxDFType *sampled_type) const {
  *wi = cosine_sample_hemisphere(sample);
  if (wo.z > 0)
    wi->z *= -1;
  *p = pdf(wo, *wi);
  return f(wo, *wi);
}
specula::Float specula::LambertianTransmission::pdf(const Vector3f &wo,
                                                    const Vector3f &wi) const {
  return !same_hemisphere(wo, wi) ? abs_cos_theta(wi) * INV_PI : 0;
}
specula::Spectrum
specula::MicrofacetReflection::sample_f(const Vector3f &wo, Vector3f *wi,
                                        const Point2f &sample, Float *p,
                                        BxDFType *sampled_type) const {
  if (wo.z == 0)
    return 0.0;
  Vector3f wh = distribution->sample_wh(wo, sample);
  if (dot(wo, wh) < 0)
    return 0.0f;
  *wi = reflect(wo, wh);
  if (!same_hemisphere(wo, *wi))
    return Spectrum(0.0f);
  *p = distribution->pdf(wo, wh) / (4 * dot(wo, wh));
  return f(wo, *wi);
}
specula::Float specula::MicrofacetReflection::pdf(const Vector3f &wo,
                                                  const Vector3f &wi) const {
  if (!same_hemisphere(wo, wi))
    return 0;
  Vector3f wh = normalize(wo + wi);
  return distribution->pdf(wo, wh) / (4 * dot(wo, wh));
}
specula::Spectrum
specula::MicrofacetTransmission::sample_f(const Vector3f &wo, Vector3f *wi,
                                          const Point2f &sample, Float *p,
                                          BxDFType *sampled_type) const {
  if (wo.z == 0)
    return 0.0;
  Vector3f wh = distribution->sample_wh(wo, sample);
  if (dot(wo, wh) < 0)
    return 0.0f;
  Float eta = cos_theta(wo) > 0 ? (etaa / etab) : (etab / etaa);
  if (!refract(wo, (Normal3f)(wh), eta, wi))
    return 0;
  *p = pdf(wo, *wi);
  return f(wo, *wi);
}
specula::Float specula::MicrofacetTransmission::pdf(const Vector3f &wo,
                                                    const Vector3f &wi) const {
  if (same_hemisphere(wo, wi))
    return 0;
  Float eta = cos_theta(wo) > 0 ? (etab / etaa) : (etaa / etab);
  Vector3f wh = normalize(wo + wi * eta);

  Float sqrt_denom = dot(wo, wh) + eta * dot(wi, wh);
  Float dwh_dwi =
      std::abs((eta * eta * dot(wi, wh)) / (sqrt_denom * sqrt_denom));
  return distribution->pdf(wo, wh) * dwh_dwi;
}
specula::Spectrum
specula::FresnelBlend::sample_f(const Vector3f &wo, Vector3f *wi,
                                const Point2f &u_orig, Float *p,
                                BxDFType *sampled_type) const {
  Point2f u = u_orig;
  if (u[0] < 0.5f) {
    u[0] = std::min(2 * u[0], one_minus_epsilon);
    *wi = cosine_sample_hemisphere(u);
    if (wo.z < 0)
      wi->z *= -1;
  } else {
    u[0] = std::min(2 * (u[0] - 0.5f), one_minus_epsilon);
    Vector3f wh = distribution->sample_wh(wo, u);
    *wi = reflect(wo, wh);
    if (!same_hemisphere(wo, *wi))
      return Spectrum(0.0f);
  }
  *p = pdf(wo, *wi);
  return f(wo, *wi);
}
specula::Float specula::FresnelBlend::pdf(const Vector3f &wo,
                                          const Vector3f &wi) const {
  if (!same_hemisphere(wo, wi))
    return 0;
  Vector3f wh = normalize(wo + wi);
  Float pdf_wh = distribution->pdf(wo, wh);
  return 0.5f * (abs_cos_theta(wi) * INV_PI + pdf_wh / (4 * dot(wo, wh)));
}
specula::Spectrum
specula::FresnelSpecular::sample_f(const Vector3f &wo, Vector3f *wi,
                                   const Point2f &u, Float *p,
                                   BxDFType *sampled_type) const {
  Float f = fr_dielectric(cos_theta(wo), etaa, etab);
  if (u[0] < f) {
    *wi = Vector3f(-wo.x, -wo.y, wo.z);
    if (sampled_type)
      *sampled_type = BxDFType(BSDF_SPECULAR | BSDF_REFLECTION);
    *p = f;
    return f * r / abs_cos_theta(*wi);
  } else {
    bool entering = cos_theta(wo) > 0;
    Float etai = entering ? etaa : etab;
    Float etat = entering ? etab : etaa;
    if (!refract(wo, faceforward(Normal3f(0, 0, 1), wo), etai / etat, wi))
      return 0;
    Spectrum ft = t * (1 - f);
    if (mode == TransportMode::RADIANCE) {
      ft *= (etai * etai) / (etat * etat);
    }
    if (sampled_type)
      *sampled_type = BxDFType(BSDF_SPECULAR | BSDF_TRANSMISSION);
    *p = 1 - f;
    return ft / abs_cos_theta(*wi);
  }
}
std::string specula::FresnelSpecular::fmt() const {
  return fmt::format(
      "<BxDF.FresnelSpecular R: {} T: {} etaA: {} etaB: {} mode: {}>", r.fmt(),
      t.fmt(), etaa, etab,
      (mode == TransportMode::RADIANCE ? "RADIANCE" : "IMPORTANCE"));
}
specula::Spectrum specula::BxDF::rho(const Vector3f &w, int nsamples,
                                     const Point2f *u) const {
  Spectrum r(0.0);
  for (int i = 0; i < nsamples; ++i) {
    Vector3f wi;
    Float pdf = 0;
    Spectrum f = sample_f(w, &wi, u[i], &pdf);
    if (pdf > 0)
      r += f * abs_cos_theta(wi) / pdf;
  }
  return r / nsamples;
}
specula::Spectrum specula::BxDF::rho(int samples, const Point2f *u1,
                                     const Point2f *u2) const {
  Spectrum r(0.0f);
  for (int i = 0; i < samples; ++i) {
    Vector3f wo, wi;
    wo = uniform_sample_hemisphere(u1[i]);
    Float pdfo = uniform_hemisphere_pdf(), pdfi = 0;
    Spectrum f = sample_f(wo, &wi, u2[i], &pdfi);
    if (pdfi > 0)
      r += f * abs_cos_theta(wi) * abs_cos_theta(wo) / (pdfo * pdfi);
  }
  return r / (PI * samples);
}
specula::Spectrum specula::BSDF::f(const Vector3f &wow, const Vector3f &wiw,
                                   BxDFType flags) const {
  PROF_FUNC();
  Vector3f wi = world_to_local(wiw), wo = world_to_local(wow);
  if (wo.z == 0)
    return 0;
  bool reflect = dot(wiw, ng) * dot(wow, ng) > 0;
  Spectrum f(0.0f);
  for (int i = 0; i < nBxDFs; ++i) {
    if (bxdfs[i]->matches_flags(flags) &&
        ((reflect && (bxdfs[i]->type & BSDF_REFLECTION)) ||
         (!reflect && (bxdfs[i]->type * BSDF_TRANSMISSION))))
      f += bxdfs[i]->f(wo, wi);
  }
  return f;
}
specula::Spectrum specula::BSDF::rho(int samples, const Point2f *samples1,
                                     const Point2f *samples2,
                                     BxDFType flags) const {
  Spectrum ret(0.0f);
  for (int i = 0; i < nBxDFs; ++i) {
    if (bxdfs[i]->matches_flags(flags))
      ret += bxdfs[i]->rho(samples, samples1, samples2);
  }
  return ret;
}
specula::Spectrum specula::BSDF::rho(const Vector3f &wo_world, int nsamples,
                                     const Point2f *samples,
                                     BxDFType flags) const {
  Vector3f wo = world_to_local(wo_world);
  Spectrum ret(0.0f);
  for (int i = 0; i < nBxDFs; ++i) {
    if (bxdfs[i]->matches_flags(flags))
      ret += bxdfs[i]->rho(wo, nsamples, samples);
  }
  return ret;
}
specula::Spectrum specula::BSDF::sample_f(const Vector3f &wo_world,
                                          Vector3f *wi_world, const Point2f &u,
                                          Float *p, BxDFType type,
                                          BxDFType *sampled_type) const {
  PROF_FUNC();
  int matching_comps = num_components(type);
  if (matching_comps == 0) {
    *p = 0;
    if (sampled_type)
      *sampled_type = BxDFType(0);
    return Spectrum(0);
  }
  int comp =
      std::min((int)std::floor(u[0] * matching_comps), matching_comps - 1);
  BxDF *bxdf = nullptr;
  int count = comp;
  for (int i = 0; i < nBxDFs; ++i) {
    if (bxdfs[i]->matches_flags(type) && count-- == 0) {
      bxdf = bxdfs[i];
      break;
    }
  }
  CHECK(bxdf != nullptr);
  LINFO("BSDF::sample_f chose comp = {} / matching = {}, bxdf: {}", comp,
        matching_comps, bxdf->fmt());
  Point2f uremapped(std::min(u[0] * matching_comps - comp, one_minus_epsilon),
                    u[1]);
  Vector3f wi, wo = world_to_local(wo_world);
  if (wo.z == 0)
    return 0.0f;
  *p = 0;
  if (sampled_type)
    *sampled_type = bxdf->type;
  Spectrum f = bxdf->sample_f(wo, &wi, uremapped, p, sampled_type);
  LINFO("For wo = {}, sampled f = {}, pdf = {}, ratio = {}, wi = {}", wo, f, *p,
        ((*p > 0) ? (f / *p) : Spectrum(0.0)), wi);
  if (*p == 0) {
    if (sampled_type)
      *sampled_type = BxDFType(0);
    return 0;
  }
  *wi_world = local_to_world(wi);

  if (!(bxdf->type * BSDF_SPECULAR) && matching_comps > 1) {
    for (int i = 0; i < nBxDFs; i++) {
      if (bxdfs[i] != bxdf && bxdfs[i]->matches_flags(type))
        *p += bxdfs[i]->pdf(wo, wi);
    }
  }
  if (matching_comps > 1)
    *p /= matching_comps;

  if (!(bxdf->type & BSDF_SPECULAR)) {
    bool reflect = dot(*wi_world, ng) * dot(wo_world, ng) > 0;
    f = 0.0f;
    for (int i = 0; i < nBxDFs; ++i) {
      if (bxdfs[i]->matches_flags(type) &&
          ((reflect && (bxdfs[i]->type * BSDF_REFLECTION)) ||
           (!reflect && (bxdfs[i]->type & BSDF_TRANSMISSION))))
        f += bxdfs[i]->f(wo, wi);
    }
  }
  LINFO("Overall f = {}, pdf = {}, ratio = {}", f, *p,
        ((*p > 0) ? (f / *p) : Spectrum(0.0f)));
  return f;
}
specula::Float specula::BSDF::pdf(const Vector3f &wo_world,
                                  const Vector3f &wi_world,
                                  BxDFType flags) const {
  PROF_FUNC();
  if (nBxDFs == 0.0f)
    return 0.0f;
  Vector3f wo = world_to_local(wo_world), wi = world_to_local(wi_world);
  if (wo.z == 0)
    return 0.0f;
  Float p = 0.0f;
  int matching_comps = 0;
  for (int i = 0; i < nBxDFs; ++i) {
    if (bxdfs[i]->matches_flags(flags)) {
      ++matching_comps;
      p += bxdfs[i]->pdf(wo, wi);
    }
  }
  Float v = matching_comps > 0 ? p / matching_comps : 0.0f;
  return v;
}
std::string specula::BSDF::fmt() const {
  std::string ret =
      fmt::format("<BSDF eta: {} nBxDFs: {} BxDFs: [", eta, nBxDFs);
  for (int i = 0; i < nBxDFs; ++i) {
    ret +=
        fmt::format("{}{}", bxdfs[i]->fmt(), (i == (nBxDFs - 1)) ? ']' : ',');
  }
  return ret;
}
