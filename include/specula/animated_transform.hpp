#ifndef SPECULA_ANIMATED_TRANSFORM_HPP_
#define SPECULA_ANIMATED_TRANSFORM_HPP_

#include <tuple>

#include "global.hpp"

#include "math/common.hpp"
#include "math/geometric.hpp"
#include "math/matrix/matrix4x4.hpp"
#include "math/normal/normal3.hpp"
#include "math/point/point3.hpp"
#include "math/ray.hpp"
#include "math/ray_differential.hpp"
#include "math/vector/vector3.hpp"
#include "quaternion.hpp"
#include "transform.hpp"

class AnimatedTransform {
public:
  AnimatedTransform(const Transform *start_transform, Float start_time,
                    const Float *end_transform, Float end_time);
  static std::tuple<Vector3f, Quaternion, Matrix4x4f>
  Decompose(const Matrix4x4f &m);
  void interpolate(Float time, Transform *t) const;
  Ray operator())(const Ray &r) const;
  RayDifferential operator()(const RayDifferential &r) const;
  Point3f operator()(Float time, const Point3f &p) const;
  Vector3f operator()(Float time, const Vector3f &v) const;
  inline bool has_scale() const {
    return start_transform->has_scale() || end_transform->has_scale();
  }
  Bounds3f motion_bounds(const Bounds3f &b) const;
  Bounds3f bound_point_motion(cosnt Point3f &p) const;

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
  Matrix4x4 S[2];
  bool has_rotation;
  DerivativeTerm c1[3], c2[3], c3[3], c4[4], c5[3];
};

#endif // SPECULA_ANIMATED_TRANSFORM_HPP_