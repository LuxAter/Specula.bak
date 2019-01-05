#ifndef SPECULA_OBJECT_DISTANCE_ESTIMATOR_HPP_
#define SPECULA_OBJECT_DISTANCE_ESTIMATOR_HPP_

#include <functional>

#include "../math/math.hpp"

namespace specula {
namespace object {
  inline std::function<double(const math::Vec3d&)> Sphere(double radius) {
    return [radius](const math::Vec3d& p) { return math::length(p) - radius; };
  }
  inline std::function<double(const math::Vec3d&)> Box(math::Vec3d box) {
    return [box](const math::Vec3d& p) {
      math::Vec3d d = math::abs(p) - box;
      return math::length(math::max(d, 0.0)) +
             math::min(math::max(d.x, math::max(d.y, d.z)), 0.0);
    };
  }
  inline std::function<double(const math::Vec3d&)> RoundedBox(math::Vec3d box,
                                                              double radius) {
    return [box, radius](const math::Vec3d& p) {
      math::Vec3d d = math::abs(p) - box;
      return math::length(math::max(d, 0.0)) - radius +
             math::min(math::max(d.x, math::max(d.y, d.z)), 0.0);
    };
  }
  inline std::function<double(const math::Vec3d&)> Torus(math::Vec2d torus) {
    return [torus](const math::Vec3d& p) {
      math::Vec2d q(math::length(p.xz()) - torus.x, p.y);
      return math::length(q) - torus.y;
    };
  }
  inline std::function<double(const math::Vec3d&)> Cylinder(
      math::Vec3d cylinder) {
    return [cylinder](const math::Vec3d& p) {
      return math::length(p.xz() - cylinder.xy()) - cylinder.z;
    };
  }
  // Cone must be normalized
  inline std::function<double(const math::Vec3d&)> Cone(math::Vec2d cone) {
    return [cone](const math::Vec3d& p) {
      double q = math::length(p.xy());
      return math::dot(cone, math::Vec2d(q, p.z));
    };
  }
  // plane must be normalized
  inline std::function<double(const math::Vec3d&)> Plane(math::Vec4d plane) {
    return [plane](const math::Vec3d& p) {
      return math::dot(p, plane.xyz()) + plane.w;
    };
  }
  inline std::function<double(const math::Vec3d&)> HexPrism(
      math::Vec2d hex_prism) {
    return [hex_prism](const math::Vec3d& p) {
      const math::Vec3d k(-0.8660254, 0.5, 0.57735);
      math::Vec3d pp = math::abs(p);
      pp.x -= 2.0 * math::min(math::dot(k.xy(), p.xy()), 0.0) * k.x;
      pp.y -= 2.0 * math::min(math::dot(k.xy(), p.xy()), 0.0) * k.y;
      math::Vec2d d(
          math::length(p.xy() - math::Vec2d(math::clamp(p.x, -k.z * hex_prism.x,
                                                        k.z * hex_prism.x),
                                            hex_prism.x)) *
              math::sign(p.y - hex_prism.x),
          p.z - hex_prism.y);
      return math::min(math::max(d.x, d.y), 0.0) +
             math::length(math::max(d, 0.0));
    };
  }
  inline std::function<double(const math::Vec3d&)> TriPrism(
      math::Vec2d tri_prism) {
    return [tri_prism](const math::Vec3d& p) {
      math::Vec3d q = math::abs(p);
      return math::max(
          q.z - tri_prism.y,
          math::max(q.x * 0.866025 + p.y * 0.5, -p.y) - tri_prism.x * 0.5);
    };
  }
  inline std::function<double(const math::Vec3d&)> Line(math::Vec3d a,
                                                        math::Vec3d b,
                                                        double radius) {
    return [a, b, radius](const math::Vec3d& p) {
      math::Vec3d pa = p - a, ba = b - a;
      double h = math::clamp(math::dot(pa, ba) / math::dot(ba, ba), 0.0, 1.0);
      return math::length(pa - ba * h) - radius;
    };
  }
  inline std::function<double(const math::Vec3d&)> VerticalLine(double height,
                                                                double radius) {
    return [height, radius](const math::Vec3d& p) {
      math::Vec3d q(p.x, p.y - math::clamp(p.y, 0.0, height), p.z);
      return math::length(q) - radius;
    };
  }
  inline std::function<double(const math::Vec3d&)> CappedCylinder(
      math::Vec2d cylinder) {
    return [cylinder](const math::Vec3d& p) {
      math::Vec2d d =
          math::abs(math::Vec2(math::length(p.xz()), p.y)) - cylinder;
      return math::min(math::max(d.x, d.y), 0.0) +
             math::length(math::max(d, 0.0));
    };
  }
  inline std::function<double(const math::Vec3d&)> RoundedCylinder(double ra,
                                                                   double rb,
                                                                   double h) {
    return [ra, rb, h](const math::Vec3d& p) {
      math::Vec2d d(math::length(p.xz()) - 2.0 * ra + rb, math::abs(p.y) - h);
      return math::min(math::max(d.x, d.y), 0.0) +
             math::length(math::max(d, 0.0)) - rb;
    };
  }
  inline std::function<double(const math::Vec3d&)> CappedCone(double h,
                                                              double r1,
                                                              double r2) {
    return [h, r1, r2](const math::Vec3d& p) {
      math::Vec2d q(math::length(p.xz()), p.y);
      math::Vec2d k1(r2, h), k2(r2 - r1, 2.0 * h),
          ca(q.x - math::min(q.x, (q.y < 0.0) ? r1 : r2), math::abs(q.y) - h),
          cb(q - k1 +
             k2 * math::clamp(math::dot(k1 - q, k2) / math::dot(k2, k2), 0.0,
                              1.0));
      double s = (cb.x < 0.0 && ca.y < 0.0) ? -1.0 : 1.0;
      return s * math::sqrt(math::min(math::dot(ca, ca), math::dot(cb, cb)));
    };
  }

}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_DISTANCE_ESTIMATOR_HPP_
