#ifndef SPECULA_CORE_CAMERA_HPP_
#define SPECULA_CORE_CAMERA_HPP_

#include "core/transform/animated_transform.hpp"
#include "film.hpp"
#include "geometry.hpp"
#include "specula/global.hpp"

namespace specula {

struct CameraSample {
  Point2f film;
  Point2f lens;
  Float time;
};

class Camera {
public:
  Camera(const AnimatedTransform &camera_to_world, Float shutter_open,
         Float shutter_close, Film *film, const Medium *medium);
  virtual ~Camera();
  virtual Float generate_ray(const CameraSample &sample, Ray *ray) const = 0;
  virtual Float generate_ray_differential(const CameraSample &sample,
                                          RayDifferential *rd) const;
  virtual Spectrum we(const Ray &ray, Point2f *raster2 = nullptr) const;
  virtual void pdf_we(const Ray &ray, Float *pdf_pos, Float *pdf_dir) const;
  virtual Spectrum sample_wi(const Interaction &ref, const Point2f &u,
                             Vector3f *wi, Float *pdf, Point2f *raster,
                             VisibilityTester *vis) const;

  AnimatedTransform camera_to_world;
  const Float shutter_open, shutter_close;
  Film *film;
  const Medium *medium;
};

class ProjectiveCamera : public Camera {
public:
  ProjectiveCamera(const AnimatedTransform &camera_to_world,
                   const Transform &camera_to_screen,
                   const Bounds2f &screen_window, Float shutter_open,
                   Float shutter_close, Float lensr, Float focald, Film *film,
                   const Medium *medium)
      : Camera(camera_to_world, shutter_open, shutter_close, film, medium),
        camera_to_screen(camera_to_screen), lens_radius(lensr),
        focal_distance(focald) {
    screen_to_raster =
        scale(film->full_resolution.x, film->full_resolution.y, 1) *
        scale(1 / (screen_window.p_max.x - screen_window.p_min.x),
              1 / (screen_window.p_min.y - screen_window.p_max.y), 1) *
        translate(Vector3f(-screen_window.p_min.x, -screen_window.p_max.y, 0));
    raster_to_screen = inverse(screen_to_raster);
    raster_to_camera = inverse(camera_to_screen) * raster_to_screen;
  }

protected:
  Transform camera_to_screen, raster_to_camera;
  Transform screen_to_raster, raster_to_screen;
  Float lens_radius, focal_distance;
};

inline std::ostream &operator<<(std::ostream &os, const CameraSample &cs) {
  return os << fmt::format("<CameraSample film: {}, lens: {}, time: {}>",
                           cs.film.fmt(), cs.lens.fmt(), cs.time);
}
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_CAMERA_HPP_ */
