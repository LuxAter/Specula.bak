#include "specula/core/interaction.hpp"

specula::Interaction::Interaction() : time(0) {}
specula::Interaction::Interaction(const Point3f &p, const Normal3f &n,
                                  const Vector3f &p_error, const Vector3f &wo,
                                  Float time,
                                  const MediumInterface &medium_interface)
    : p(p), time(time), p_error(p_error), wo(wo), n(n),
      medium_interface(medium_interface) {}
specula::Interaction::Interaction(const Point3f &p, const Vector3f &wo,
                                  Float time,
                                  const MediumInterface &medium_interface)
    : p(p), time(time), wo(wo), medium_interface(medium_interface) {}
specula::Interaction::Interaction(const Point3f &p, Float time,
                                  const MediumInterface &medium_interface)
    : p(p), time(time), medium_interface(medium_interface) {}

specula::Ray specula::Interaction::spawn_ray(const Vector3f &d) const {
  Point3f o = offset_ray_origin(p, p_error, n, d);
  return Ray(o, d, INFTY, time, get_medium(d));
}
specula::Ray specula::Interaction::spawn_ray_to(const Point3f &p2) const {
  Point3f origin = offset_ray_origin(p, p_error, n, p2 - p);
  Vector3f d = p2 - p;
  return Ray(origin, d, 1 - SHADOW_EPSILON, time, get_medium(d));
}
specula::Ray specula::Interaction::spawn_ray_to(const Interaction &it) const {
  Point3f origin = offset_ray_origin(p, p_error, n, it.p - p);
  Point3f target = offset_ray_origin(it.p, it.p_error, it.n, origin - it.p);
  Vector3f d = target - origin;
  return Ray(origin, d, 1 - SHADOW_EPSILON, time, get_medium(d));
}

const specula::Medium *specula::Transform::get_medium(const Vector3f &w) const {
  return dot(w, n) > 0 ? medium_interface.outside : medium_interface.inside;
}
const specula::Medium *specula::Transform::get_medium() const {
  CHECK_EQ(medium_interface.inside, medium_interface.outside);
  return medium_interface.inside;
}

specula::MediumInteraction::MediumInteraction() : phase(nullptr) {}
specula::MediumInteraction::MediumInteraction(const Point3f &p,
                                              const Vector3f &wo, Float time,
                                              const Medium *medium,
                                              const PhaseFunction *phase)
    : Interaction(p, wo, time, medium), phase(phase) {}

specula::SurfaceInteraction::SurfaceInteraction() {}
specula::SurfaceInteraction::SurfaceInteraction(
    const Point3f &p, const Vector3f &p_error, const Point2f &uv,
    const Vector3f &wo, const Vector3f &dpdu, const Vector3f &dpdv,
    const Normal3f &dndu, const Normal3f &dndv, Float time, const Shape *shape,
    int face_index)
    : Interaction(p, Normal3f(normalize(cross(dpdu, dpdv))), p_error, wo, time,
                  nullptr),
      uv(uv), dpdu(dpdu), dpdv(dpdv), dndu(dndu), dndv(dndv),
      face_index(face_index) {
  shading.n = n;
  shading.dpdu = dpdu;
  shading.dpdv = dpdv;
  shading.dndu = dndu;
  shading.dndv = dndv;

  if (shape &&
      (shape->reverse_orientation ^ shape->transform_swaps_handedness)) {
    n *= -1;
    shading.n *= -1;
  }
}
void specula::SurfaceInteraction::set_shading_geometry(
    const Vector3f &dpdus, const Vector3f &dpdvs, const Normal3f &dndus,
    const Normal3f &dndvs, bool orientation_is_authoritative) {
  shading.n = normalize((Normal3f)cross(dpdus, dpdvs));
  if (orientation_is_authoritative)
    n = faceforward(n, shading.n);
  else
    shading.n = faceforward(shading.n, n);

  shading.dpdu = dpdus;
  shading.dpdv = dpdvs;
  shading.dndu = dndus;
  shading.dndv = dndvs;
}

void specula::SurfaceInteraction::compute_scattering_functions(
    const RayDifferential &ray, MemoryArena &arena, bool allow_multiple_lobes,
    TransportMode mode) {
  compute_differentials(ray);
  primitive->compute_scattering_functions(this, arena, mode,
                                          allow_multiple_lobes);
}
void specula::SurfaceInteraction::compute_differentials(
    const RayDifferential &r) {
  if (r.has_differentials) {
    Float d = dot(n, Vector3f(p.x, p.y, p.z));
    Float tx = -(dot(n, Vector3f(r.rx_origin)) - d) / dot(n, r.rx_direction);
    if (std::isinf(tx) || std::isnan(tx)) {
      dudx = dvdx = 0;
      dudy = dvdy = 0;
      dpdx = dpdy = Vector3f(0, 0, 0);
      return;
    }
    Point3f px = r.rx_origin + tx * r.rx_direction;
    Float ty = -(dot(n, Vector3f(r.ry_origin)) - d) / dot(n, r.ry_direction);
    if (std::isinf(ty) || std::isnan(ty)) {
      dudx = dvdx = 0;
      dudy = dvdy = 0;
      dpdx = dpdy = Vector3f(0, 0, 0);
      return;
    }
    Point3f py = r.ry_origin + ty * r.ry_direction;
    dpdx = px - p;
    dpdy = py - p;

    int dim[2];
    if (std::abs(n.x) > std::abs(n.y) && std::abs(n.x) > std::abs(n.z)) {
      dim[0] = 1;
      dim[1] = 2;
    } else if (std::abs(n.y) > std::abs(n.z)) {
      dim[0] = 0;
      dim[1] = 2;
    } else {
      dim[0] = 0;
      dim[1] = 1;
    }

    Float a[2][2] = {{dpdu[dim[0]], dpdv[dim[0]]},
                     {dpdu[dim[1]], dpdv[dim[1]]}};
    Float bx[2] = {px[dim[0]] - p[dim[0]], px[dim[1]] - p[dim[1]]};
    Float by[2] = {py[dim[0]] - p[dim[0]], py[dim[1]] - p[dim[1]]};
    if (!solve_linear_system2x2(a, bx, &dudx, &dvdx))
      dudx = dvdx = 0;
    if (!solve_linear_system2x2(a, by, &dudy, &dvdy))
      dudy = dvdy = 0;
  } else {
    dudx = dvdx = 0;
    dudy = dvdy = 0;
    dpdx = dpdy = Vector3f(0, 0, 0);
  }
}
specula::Spectrum specula::SurfaceInteraction::le(const Vector3f &w) const {
  const AreaLight *area = primitive->get_area_light();
  return area ? area->l(*this, w) : Spectrum(0.0f);
}
