#include "specula/core/material.hpp"
#include "specula/core/interaction.hpp"
#include "specula/core/texture.hpp"

specula::Material::~Material() {}

void specula::Material::bump(const std::shared_ptr<Texture<Float>> &d,
                             SurfaceInteraction *si) {
  SurfaceInteraction si_eval = *si;
  Float du = 0.5f * (std::abs(si->dudx) + std::abs(si->dudy));
  if (du == 0)
    du = 0.0005f;
  si_eval.p = si->p + du * si->shading.dpdu;
  si_eval.uv = si->uv + Vector2f(du, 0.0f);
  si_eval.n = normalize(Normal3f(cross(si->shading.dpdu, si->shading.dpdv)) +
                        du * si->dndu);
  Float udisplace = d->evaluate(si_eval);

  Float dv = 0.5f * (std::abs(si->dvdx) + std::abs(si->dvdy));
  if (dv == 0)
    dv = 0.0005f;
  si_eval.p = si->p + dv * si->shading.dpdv;
  si_eval.uv = si->uv + Vector2f(0.0f, dv);
  si_eval.n = normalize(Normal3f(cross(si->shading.dpdu, si->shading.dpdv)) +
                        dv * si->dndv);
  Float vdisplace = d->evaluate(si_eval);
  Float displace = d->evaluate(*si);

  Vector3f dpdu = si->shading.dpdu +
                  (udisplace - displace) / du * Vector3f(si->shading.n) +
                  displace * Vector3f(si->shading.dndu);
  Vector3f dpdv = si->shading.dpdv +
                  (vdisplace - displace) / dv * Vector3f(si->shading.n) +
                  displace * Vector3f(si->shading.dndv);
  si->set_shading_geometry(dpdu, dpdv, si->shading.dndu, si->shading.dndv,
                           false);
}
