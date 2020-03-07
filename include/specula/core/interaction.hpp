#ifndef SPECULA_CORE_INTERACTION_HPP_
#define SPECULA_CORE_INTERACTION_HPP_

#include "../global.hpp"
#include "core/geometry/common.hpp"
#include "geometry.hpp"

namespace specula {
struct Interaction {
  Interaction();
  Interaction(const Point3f &p, const Normal3f &n, const Vector3f &p_error,
              const Vector3f &wo, Float time,
              const MediumInterface &medium_interface);
  Interaction(const Point3f &p, const Vector3f &wo, Float time,
              const MediumInterface &medium_interface);
  Interaction(const Point3f &p, Float time,
              const MediumInterface &medium_interface);

  inline bool is_surface_interaction() const { return n != Normal3f(); }
  inline bool is_medium_interaction() const {
    return !is_surface_interaction();
  }

  Ray spawn_ray(const Vector3f &d) const;
  Ray spawn_ray_to(const Point3f &p2) const;
  Ray spawn_ray_to(const Interaction &it) const;

  const Medium *get_medium(const Vector3f &w) const;
  const Medium *get_medium() const;

  Point3f p;
  Float time;
  Vector3f p_error;
  Vector3f wo;
  Normal3f n;
  MediumInterface medium_interface;
};

struct MediumInteraction : public Interaction {
  MediumInteraction();
  MediumInteraction(const Point3f &p, const Vector3f &wo, Float time,
                    const Medium *medium, const PhaseFunction *phase);
  inline bool is_valid() const { return phase != nullptr; }

  const PhaseFunction *phase;
};

struct SurfaceInteraction : public Interaction {
  SurfaceInteraction();
  SurfaceInteraction(const Point3f &p, const Vector3f &p_error,
                     const Point2f &uv, const Vector3f &wo,
                     const Vector3f &dpdu, const Vector3f &dpdv,
                     const Normal3f &dndu, const Normal3f &dndv, Float time,
                     const Shape *shape, int face_index = 0);

  void set_shading_geometry(const Vector3f &dpdus, const Vector3f &dpdvs,
                            const Normal3f &dndus, const Normal3f &dndvs,
                            bool orientation_is_authoritative);
  void
  compute_scattering_functions(const RayDifferential &ray, MemoryArena &arena,
                              bool allow_multiple_lobes = false,
                              TransportMode mode = TransportMode::Radiance);
  void compute_differentials(const RayDifferential &r);
  Spectrum le(const Vector3f &w) const;

  Point2f uv;
  Vector3f dpdu, dpdv;
  Normal3f dndu, dndv;
  const Shape *shape = nullptr;
  struct {
    Normal3f n;
    Vector3f dpdu, dpdv;
    Normal3f dndu, dndv;
  } shading;
  const Primitive *primitive = nullptr;
  BSDF *bsdf = nullptr;
  BSSRDF *bssrdf = nullptr;
  mutable Vector3f dpdx, dpdy;
  mutable Float dudx = 0, dvdx = 0, dudy = 0, dvdy = 0;
  int face_index = 0;
};
} // namespace specula

#endif // SPECULA_CORE_INTERACTION_HPP_
