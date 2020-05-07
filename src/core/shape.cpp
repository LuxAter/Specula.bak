#include "specula/core/shape.hpp"
#include "core/interaction.hpp"
#include "core/medium.hpp"
#include "core/transform/transform.hpp"

specula::Shape::Shape(const Transform *object_to_world,
                      const Transform *world_to_object,
                      bool reverse_orientation)
    : object_to_world(object_to_world), world_to_object(world_to_object),
      reverse_orientation(reverse_orientation),
      transform_swaps_handedness(object_to_world->swaps_handedness()) {}

specula::Shape::~Shape() {}

specula::Bounds3f specula::Shape::world_bounds() const {
  return object_to_world->op(object_bounds());
}
specula::Interaction specula::Shape::sample(const Interaction &ref,
                                            const Point2f &u,
                                            Float *pdf) const {
  Interaction intr = sample(u, pdf);
  Vector3f wi = intr.p - ref.p;
  if (wi.length_squared() == 0)
    *pdf = 0.0f;
  else {
    wi = normalize(wi);
    *pdf *= distance_squared(ref.p, intr.p) / abs_dot(intr.n, -wi);
  }
  return intr;
}

specula::Float specula::Shape::pdf(const Interaction &ref,
                                   const Vector3f &wi) const {
  Ray ray = ref.spawn_ray(wi);
  Float thit;
  SurfaceInteraction isect_light;
  if (!intersect(ray, &thit, &isect_light, false))
    return 0;
  Float pdf = distance_squared(ref.p, isect_light.p) /
              (abs_dot(isect_light.n, -wi) * area());
  if (std::isinf(pdf))
    pdf = 0.0f;
  return pdf;
}

specula::Float specula::Shape::solid_angle(const Point3f &p,
                                           int nsamples) const {
  Interaction ref(p, Normal3f(), Vector3f(), Vector3f(0, 0, 1), 0,
                  MediumInterface{});
  double solid_angle = 0.0;
  for (int i = 0; i < nsamples; ++i) {
    // TODO
    // Point2f u{radical_inverse(0, i), radical_inverse(1, i)};
    Point2f u{0, 0};
    Float pdf;
    Interaction pshape = sample(ref, u, &pdf);
    if (pdf > 0 && !intersect(Ray(p, pshape.p - p, 0.999f))) {
      solid_angle += 1 / pdf;
    }
  }
  return solid_angle / nsamples;
}
