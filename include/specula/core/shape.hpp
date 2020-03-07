#ifndef SPEcULA_CORE_SHAPE_HPP_
#define SPEcULA_CORE_SHAPE_HPP_

#include "../global.hpp"
#include "geometry.hpp"
#include "interaction.hpp"
#include "transform.hpp"

namespace specula {
class Shape {
public:
  Shape(const Transform *object_to_world, const Transform *world_to_object,
        bool reverse_orientation);
  virtual ~Shape();
  virtual Bounds3f object_bound() const = 0;
  virtual Bounds3f world_bound() const;
  virtual bool intersect(const Ray &ray, Float *t_hit,
                         SurfaceInteraction *isect,
                         bool test_alpha_texture = true) const = 0;
  virtual bool intersect_p(const Ray &ray,
                           bool test_alpha_texture = true) const {
    return intersect(ray, nullptr, nullptr, test_alpha_texture);
  }
  virtual Float area() const = 0;
  virtual Interaction sample(const Point2f &u, Float *pdf) const = 0;
  virtual Float pdf(const Interaction &) const { return 1 / area(); }
  virtual Interaction sample(const Interaction &ref, const Point2f &u,
                             Float *pdf) const;
  virtual Float pdf(const Interaction &ref, const Vector3f &wi) const;

  virtual Float solid_angle(const Point3f& p, int n_samples = 512) const;

  const Transform* object_to_world, *world_to_object;
  const bool reverse_orientation;
  const bool transform_swaps_handedness;
};
} // namespace specula

#endif // SPEcULA_CORE_SHAPE_HPP_
