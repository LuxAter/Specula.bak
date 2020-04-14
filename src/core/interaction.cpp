#include "specula/core/interaction.hpp"

#include "core/transform/transform.hpp"
#include "specula/core/geometry.hpp"
#include "specula/core/spectrum.hpp"
#include "specula/global.hpp"

specula::SurfaceInteraction::SurfaceInteraction(
    const Point3f &p, const Vector3f &p_error, const Point2f &uv,
    const Vector3f &wo, const Vector3f &dpdu, const Vector3f &dpdv,
    const Normal3f &dndu, const Normal3f &dndv, Float time, const Shape *,
    int face_index)
    : Interaction(p, Normal3f(normalize(cross(dpdu, dpdv))), p_error, wo, time),
      uv(uv), dpdu(dpdu), dpdv(dpdv), dndu(dndu), dndv(dndv),
      face_index(face_index) {
  shading.n = n;
  shading.dpdu = dpdu;
  shading.dpdv = dpdv;
  shading.dndu = dndu;
  shading.dndv = dndv;

  // TODO SHAPE ADJUST NORMAL
}

void specula::SurfaceInteraction::set_shading_geometry(
    const Vector3f &dpdu, const Vector3f &dpdv, const Normal3f &dndu,
    const Normal3f &dndv, bool orientation_is_authoritative) {
  shading.n = normalize(static_cast<Normal3f>(cross(dpdu, dpdv)));
  if (orientation_is_authoritative) {
    n = faceforward(n, shading.n);
  } else {
    shading.n = faceforward(shading.n, n);
  }

  shading.dpdu = dpdu;
  shading.dpdv = dpdv;
  shading.dndu = dndu;
  shading.dndv = dndv;
}
// TODO: Add transport mode
void specula::SurfaceInteraction::compute_scattering_function(
    const RayDifferential &ray, MemoryArena *arena, bool allow_multiple_lobes) {
  compute_differentials(ray);
  // TODO: Primative compute scattering functions
}
void specula::SurfaceInteraction::compute_differentials(
    const RayDifferential &ray) const {
  if (ray.has_differentials) {
    Float d = dot(n, Vector3f(p.x, p.y, p.z));
    Float tx =
        -(dot(n, Vector3f(ray.rx_origin)) - d) / dot(n, ray.rx_direction);
    if (std::isinf(tx) || std::isnan(tx)) {
      dudx = dvdx = 0;
      dudy = dvdy = 0;
      dpdx = dpdy = Vector3f(0, 0, 0);
      return;
    }
    Point3f px = ray.rx_origin + tx * ray.rx_direction;

    Float ty =
        -(dot(n, Vector3f(ray.ry_origin)) - d) / dot(n, ray.ry_direction);
    if (std::isinf(ty) || std::isnan(ty)) {
      dudx = dvdx = 0;
      dudy = dvdy = 0;
      dpdx = dpdy = Vector3f(0, 0, 0);
      return;
    }
    Point3f py = ray.ry_origin + ty * ray.ry_direction;

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

    if (!solve_linear_system(a, bx, &dudx, &dvdx))
      dudx = dvdx = 0;
    if (!solve_linear_system(a, by, &dudy, &dvdy))
      dudy = dvdy = 0;
  } else {
    dudx = dvdx = 0;
    dudy = dvdy = 0;
    dpdx = dpdy = Vector3f(0, 0, 0);
  }
}
specula::Spectrum specula::SurfaceInteraction::le(const Vector3f &w) const {
  // TODO
  return Spectrum(0.0f);
}
