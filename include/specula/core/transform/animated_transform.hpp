#ifndef SPECULA_CORE_TRANSFORM_ANIMATED_TRANSFORM_HPP_
#define SPECULA_CORE_TRANSFORM_ANIMATED_TRANSFORM_HPP_

#include "core/geometry/ray.hpp"
#include "core/transform/transform.hpp"
#include "specula/core/geometry.hpp"
#include "specula/core/quaternion.hpp"
#include "specula/global.hpp"

namespace specula {
class AnimatedTransform {
public:
  AnimatedTransform(const Transform *start_transform, Float start_time,
                    const Transform *end_transform, Float end_time);

  static void decompose(const Matrix4x4f &m, Vector3f *t, Quaternion *r,
                        Matrix4x4f *s);

  void interpolate(Float time, Transform *t) const;

  Ray op(const Ray &r) const;
  RayDifferential op(const RayDifferential &r) const;
  Point3f op(Float time, const Point3f &p) const;
  Vector3f op(Float time, const Vector3f &p) const;

  template <typename T, typename... Args>
  inline auto operator()(const T &v, const Args &... args) const
      -> decltype(op(v, args...)) {
    return op(v, args...);
  }

  bool has_scale() const {
    return start_transform->has_scale() || end_transform->has_scale();
  }
  Bounds3f motion_bounds(const Bounds3f &b) const;
  Bounds3f bound_point_motion(const Point3f &p) const;

private:
  struct DerivativeTerm {
    DerivativeTerm() {}
    DerivativeTerm(Float c, Float x, Float y, Float z)
        : kc(c), kx(x), ky(y), kz(z) {}
    Float kc, kx, ky, kz;
    Float eval(const Point3f &p) const {
      return kc + kx * p.x + ky * p.y + kz * p.z;
    }
  };

  const Transform *start_transform, *end_transform;
  const Float start_time, end_time;
  const bool actually_animated;
  Vector3f T[2];
  Quaternion R[2];
  Matrix4x4f S[2];
  bool has_rotation;
  DerivativeTerm c1[3], c2[3], c3[3], c4[3], c5[3];
};
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_TRANSFORM_ANIMATED_TRANSFORM_HPP_ \
        */
