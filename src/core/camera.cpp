#include "specula/core/camera.hpp"

#include "specula/core/sampler.hpp"
#include "specula/core/sampling.hpp"

specula::Camera::Camera(const AnimatedTransform &camera_to_world,
                        Float shutter_open, Float shutter_close, Film *film,
                        const Medium *medium)
    : camera_to_world(camera_to_world), shutter_open(shutter_open),
      shutter_close(shutter_close), film(film), medium(medium) {
  if (camera_to_world.has_scale()) {
    LWARN("Scaling detected in world-to-camera transformation");
  }
}
specula::Camera::~Camera() { delete film; }

specula::Float
specula::Camera::generate_ray_differential(const CameraSample &sample,
                                           RayDifferential *rd) const {
  Float wt = generate_ray(sample, rd);
  if (wt == 0)
    return 0;
  Float wtx;
  for (Float eps : {0.05, -0.05}) {
    CameraSample sample_shift = sample;
    sample_shift.film.x += eps;
    Ray rx;
    wtx = generate_ray(sample_shift, &rx);
    rd->rx_origin = rd->o + (rx.o - rd->o) / eps;
    rd->rx_direction = rd->d + (rx.d - rd->d) / eps;
    if (wtx != 0)
      break;
  }
  if (wtx == 0)
    return 0;

  Float wty;
  for (Float eps : {0.05, -0.05}) {
    CameraSample sample_shift = sample;
    sample_shift.film.y += eps;
    Ray ry;
    wty = generate_ray(sample_shift, &ry);
    rd->ry_origin = rd->o + (ry.o - rd->o) / eps;
    rd->ry_direction = rd->d + (ry.d - rd->d) / eps;
    if (wty != 0)
      break;
  }
  if (wty == 0)
    return 0;
  rd->has_differentials = true;
  return wt;
}
specula::Spectrum specula::Camera::we(const Ray &ray, Point2f *raster) const {
  LFATAL("specula::Camera::we() is not implemented");
  return Spectrum(0.0f);
}
void specula::Camera::pdf_we(const Ray &ray, Float *pdf_pos,
                             Float *pdf_dir) const {
  LFATAL("specula::Camera::pdf_we() is not implemented");
}
specula::Spectrum specula::Camera::sample_wi(const Interaction &ref,
                                             const Point2f &u, Vector3f *wi,
                                             Float *pdf, Point2f *raster,
                                             VisibilityTester *vis) const {
  LFATAL("specula::Camera::sample_wi() is not implemented");
  return Spectrum(0.0f);
}
