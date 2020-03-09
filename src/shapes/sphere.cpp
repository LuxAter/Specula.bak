#include "specula/shapes/sphere.hpp"

specula::Sphere::Sphere(const Transform *object_to_world,
                        const Transform *world_to_object,
                        bool reverse_orientation, Float radius, Float z_min,
                        Float z_max, Float phi_max)
    : Shape(object_to_world, world_to_object, reverse_orientation),
      radius(radius), z_min(clamp(std::min(z_min, z_max), -radius, radius)),
      z_max(clamp(std::max(z_min, z_max), -radius, radius)),
      theta_min(std::acos(clamp(std::min(z_min, z_max) / radius, -1, 1))),
      theta_max(std::acos(clamp(std::max(z_min, z_max) / radius, -1, 1))),
      phi_max(radians(clamp(phi_max, 0, 360))) {}
specula::Bounds3f specula::Sphere::object_bound() const {
  return Bounds3f(Point3f(-radius, -radius, z_min),
                  Point3f(radius, radius, z_max));
}
bool specula::Sphere::intersect(const Ray &ray, Float *t_hit,
                                SurfaceInteraction *isect,
                                bool test_alpha_texture) const {
  Float phi;
  Point3f p_hit;
  Vector3f o_err, d_err;
  Ray r = (*world_to_object)(ray, &o_err, &d_err);

  EFloat ox(ray.o.x, o_err.x), oy(ray.o.y, o_err.y), oz(ray.o.z, o_err.z);
  EFloat dx(ray.d.x, d_err.x), dy(ray.d.y, d_err.y), dz(ray.d.z, d_err.z);
}
bool specula::Sphere::intersect_p(const Ray &ray,
                                  bool test_alpha_texture) const {}
Float specula::Sphere::area() const {}
specula::Interaction specula::Sphere::sample(const Point2f &u,
                                             Float *pdf) const {}
specula::Interaction specula::Sphere::sample(const Interaction &ref,
                                             const Point2f &u,
                                             Float *pdf) const {}
Float specula::Sphere::pdf(const Interaction &ref, const Vector3f &wi) const {}

Float specula::Sphere::solid_angle(const Point3f &p, int n_samples) const {}
