#ifndef SPECULA_CORE_INTERACTION_HPP_
#define SPECULA_CORE_INTERACTION_HPP_

#include "geometry.hpp"
#include "spectrum.hpp"
#include "specula/global.hpp"

namespace specula {
// TODO: Add medium interface when available.
struct Interaction {
  Interaction() : time(0) {}
  Interaction(const Point3f &p, const Normal3f &n, const Vector3f &p_error,
              const Vector3f &wo, Float time)
      : p(p), time(time), p_error(p_error), wo(normalize(wo)), n(n) {}
  Interaction(const Point3f &p, const Vector3f &wo, Float time)
      : p(p), time(time), wo(wo) {}
  Interaction(const Point3f &p, Float time) : p(p), time(time) {}

  bool is_surface_interaction() const { return n != Normal3f(); }
  bool is_medium_interaction() const { return !is_surface_interaction(); }

  Ray spawn_ray(const Vector3f &d) const {
    Point3f o = offset_ray_origin(p, p_error, n, d);
    return Ray(o, d, INFTY, time, get_medium(d));
  }
  Ray spawn_ray(const Point3f &p2) const {
    Vector3f d = p2 - p;
    Point3f o = offset_ray_origin(p, p_error, n, d);
    return Ray(o, d, 1 - SHADOW_EPSILON, time, get_medium(d));
  }
  Ray spawn_ray_to(const Interaction &it) const {
    Point3f origin = offset_ray_origin(p, p_error, n, it.p - p);
    Point3f target = offset_ray_origin(it.p, it.p_error, it.n, origin - it.p);
    Vector3f d = target - origin;
    return Ray(origin, d, 1 - SHADOW_EPSILON, time, get_medium(d));
  }

  const Medium *get_medium(const Vector3f &w) const { return nullptr; }
  const Medium *get_medium() const { return nullptr; }

  Point3f p;
  Float time;
  Vector3f p_error, wo;
  Normal3f n;
};

class MediumInteraction : public Interaction {
public:
  MediumInteraction() : phase(nullptr) {}
  MediumInteraction(const Point3f &p, const Vector3f &wo, Float time,
                    const Medium *medium, const PhaseFunction *phase)
      : Interaction(p, wo, time), phase(phase) {}

  bool is_valid() const { return phase != nullptr; }

  const PhaseFunction *phase;
};

class SurfaceInteraction : public Interaction {
public:
  SurfaceInteraction() {}
  SurfaceInteraction(const Point3f &p, const Vector3f &p_error,
                     const Point2f &uv, const Vector3f &wo,
                     const Vector3f &dpdu, const Vector3f &dpdv,
                     const Normal3f &dndu, const Normal3f &dndv, Float time,
                     const Shape *sh, int face_index = 0);

  void set_shading_geometry(const Vector3f &dpdu, const Vector3f &dpdv,
                            const Normal3f &dndu, const Normal3f &dndv,
                            bool orientation_is_authoritative);
  // TODO: Add transport mode
  void compute_scattering_function(const RayDifferential &ray,
                                   MemoryArena *arena,
                                   bool allow_multiple_lobes = false);
  void compute_differentials(const RayDifferential &ray) const;
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

#endif /* end of include guard: SPECULA_CORE_INTERACTION_HPP_ */
