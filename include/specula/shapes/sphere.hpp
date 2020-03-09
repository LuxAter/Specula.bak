#ifndef SPECULA_SHAPES_SPHERE_HPP_
#define SPECULA_SHAPES_SPHERE_HPP_

#include "../core/shape.hpp"

namespace specula {
class Sphere : public Shape {
public:
  Sphere(const Transform *object_to_world, const Transform *world_to_object,
         bool reverse_orientation, Float radius, Float z_min, Float z_max,
         Float phi_max);
  Bounds3f object_bound() const override;
  bool intersect(const Ray &ray, Float *t_hit, SurfaceInteraction *isect,
                 bool test_alpha_texture) const override;
  bool intersect_p(const Ray &ray, bool test_alpha_texture) const override;
  Float area() const override;
  Interaction sample(const Point2f &u, Float *pdf) const override;
  Interaction sample(const Interaction &ref, const Point2f &u,
                     Float *pdf) const override;
  Float pdf(const Interaction &ref, const Vector3f &wi) const override;

  Float solid_angle(const Point3f &p, int n_samples) const override;

private:
  const Float radius;
  const Float z_min, z_max;
  const Float theta_min, theta_max, phi_max;
};

std::shared_ptr<Shape> create_sphere_shape(const Transform *o2w,
                                           const Transform *w2o,
                                           bool reverse_orientation,
                                           const ParamSet &params);

} // namespace specula

#endif // SPECULA_SHAPES_SPHERE_HPP_
