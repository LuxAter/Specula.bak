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
  // {ring radius, radius of torus}
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
  inline std::function<double(const math::Vec3d&)> RoundedCone(double h,
                                                               double r1,
                                                               double r2) {
    return [h, r1, r2](const math::Vec3d& p) {
      math::Vec2d q(math::length(p.xz()), p.y);
      double b = (r1 - r2) / h;
      double a = math::sqrt(1.0 - b * b);
      double k = math::dot(q, math::Vec2d(-b, a));
      if (k < 0.0) return math::length(q) - r1;
      if (k > a * h) return math::length(q - math::Vec2d(0.0, h)) - r2;
      return math::dot(q, math::Vec2d(a, b)) - r1;
    };
  }
  inline std::function<double(const math::Vec3d&)> Ellipsoid(math::Vec3d r) {
    return [r](const math::Vec3d& p) {
      double k0 = math::length(p / r);
      double k1 = math::length(p / (r * r));
      return k0 * (k0 - 1.0) / k1;
    };
  }
  inline std::function<double(const math::Vec3d&)> Triangle(math::Vec3d a,
                                                            math::Vec3d b,
                                                            math::Vec3d c) {
    return [a, b, c](const math::Vec3d& p) {
      math::Vec3d ba = b - a, pa = p - a, cb = c - b, pb = p - b, ac = a - c,
                  pc = p - c;
      math::Vec3d nor = math::cross(ba, ac);
      return math::sqrt(
          (math::sign(math::dot(math::cross(ba, nor), pa)) +
               math::sign(math::dot(math::cross(cb, nor), pb)) +
               math::sign(math::dot(math::cross(ac, nor), pc)) <
           2.0)
              ? math::min(
                    math::min(math::dot2(ba * math::clamp(math::dot(ba, pa) /
                                                              math::dot2(ba),
                                                          0.0, 1.0) -
                                         pa),
                              math::dot2(cb * math::clamp(math::dot(cb, pb) /
                                                              math::dot2(cb),
                                                          0.0, 1.0) -
                                         pb)),
                    math::dot2(
                        ac * math::clamp(math::dot(ac, pc) / math::dot2(ac),
                                         0.0, 1.0) -
                        pc))
              : math::dot(nor, pa) * math::dot(nor, pa) / math::dot2(nor));
    };
  }
  inline std::function<double(const math::Vec3d&)> Quad(math::Vec3d a,
                                                        math::Vec3d b,
                                                        math::Vec3d c,
                                                        math::Vec3d d) {
    return [a, b, c, d](const math::Vec3d& p) {
      math::Vec3d ba = b - a, pa = p - a, cb = c - b, pb = p - b, dc = d - c,
                  pc = p - c, ad = a - d, pd = p - d;
      math::Vec3d nor = math::cross(ba, ad);
      return math::sqrt(
          (math::sign(math::dot(math::cross(ba, nor), pa)) +
               math::sign(math::dot(math::cross(cb, nor), pb)) +
               math::sign(math::dot(math::cross(dc, nor), pc)) +
               math::sign(math::dot(math::cross(ad, nor), pd)) <
           2.0)
              ? math::min(
                    math::min(
                        math::min(
                            math::dot2(ba * math::clamp(math::dot(ba, pa) /
                                                            math::dot2(ba),
                                                        0.0, 1.0) -
                                       pa),
                            math::dot2(cb * math::clamp(math::dot(cb, pb) /
                                                            math::dot2(cb),
                                                        0.0, 1.0) -
                                       pb)),
                        math::dot2(
                            dc * math::clamp(math::dot(dc, pc) / math::dot2(dc),
                                             0.0, 1.0) -
                            pc)),
                    math::dot2(
                        ad * math::clamp(math::dot(ad, pd) / math::dot2(ad),
                                         0.0, 1.0) -
                        pd))
              : math::dot(nor, pa) * math::dot(nor, pa) / math::dot2(nor));
    };
  }

  inline std::function<double(const math::Vec3d&)> Streach(
      std::function<double(const math::Vec3d&)> obj, math::Vec3d h) {
    return [obj, h](const math::Vec3d& p) {
      math::Vec3d q = math::abs(p) - h;
      return obj(math::max(q, 0.0)) +
             math::min(math::max(q.x, math::max(q.y, q.z)), 0.0);
    };
  }
  inline std::function<double(const math::Vec3d&)> Round(
      std::function<double(const math::Vec3d&)> obj, double radius) {
    return [obj, radius](const math::Vec3d& p) { return obj(p) - radius; };
  }
  inline std::function<double(const math::Vec3d&)> Onion(
      std::function<double(const math::Vec3d&)> obj, double thickness) {
    return [obj, thickness](const math::Vec3d& p) {
      return math::abs(obj(p)) - thickness;
    };
  }

  inline std::function<double(const math::Vec3d&)> Union(
      std::function<double(const math::Vec3d&)> obj1,
      std::function<double(const math::Vec3d&)> obj2) {
    return [obj1, obj2](const math::Vec3d& p) {
      return math::min(obj1(p), obj2(p));
    };
  }
  inline std::function<double(const math::Vec3d&)> Subtraction(
      std::function<double(const math::Vec3d&)> obj1,
      std::function<double(const math::Vec3d&)> obj2) {
    return [obj1, obj2](const math::Vec3d& p) {
      return math::max(-obj1(p), obj2(p));
    };
  }
  inline std::function<double(const math::Vec3d&)> Intersection(
      std::function<double(const math::Vec3d&)> obj1,
      std::function<double(const math::Vec3d&)> obj2) {
    return [obj1, obj2](const math::Vec3d& p) {
      return math::max(obj1(p), obj2(p));
    };
  }

  inline std::function<double(const math::Vec3d&)> SmoothUnion(
      std::function<double(const math::Vec3d&)> obj1,
      std::function<double(const math::Vec3d&)> obj2, double k) {
    return [obj1, obj2, k](const math::Vec3d& p) {
      double d1 = obj1(p), d2 = obj2(p);
      double h = math::clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0);
      return math::mix(d2, d1, h) - k * h * (1.0 - h);
    };
  }
  inline std::function<double(const math::Vec3d&)> SmoothSubtraction(
      std::function<double(const math::Vec3d&)> obj1,
      std::function<double(const math::Vec3d&)> obj2, double k) {
    return [obj1, obj2, k](const math::Vec3d& p) {
      double d1 = obj1(p), d2 = obj2(p);
      double h = math::clamp(0.5 - 0.5 * (d2 + d1) / k, 0.0, 1.0);
      return math::mix(d2, -d1, h) + k * h * (1.0 - h);
    };
  }
  inline std::function<double(const math::Vec3d&)> SmoothIntersection(
      std::function<double(const math::Vec3d&)> obj1,
      std::function<double(const math::Vec3d&)> obj2, double k) {
    return [obj1, obj2, k](const math::Vec3d& p) {
      double d1 = obj1(p), d2 = obj2(p);
      double h = math::clamp(0.5 - 0.5 * (d2 - d1) / k, 0.0, 1.0);
      return math::mix(d2, d1, h) + k * h * (1.0 - h);
    };
  }
  inline std::function<double(const math::Vec3d&)> Translate(
      std::function<double(const math::Vec3d&)> obj, math::Vec3d pos) {
    math::Mat4d t(1), it(1);
    auto res = math::translate(t, it, pos);
    it = res.second;
    return [obj, it](const math::Vec3d& p) { return obj(it * p); };
  }
  inline std::function<double(const math::Vec3d&)> Rotate(
      std::function<double(const math::Vec3d&)> obj, math::Vec3d pos) {
    math::Mat4d t(1), it(1);
    auto res = rotateX(t, it, pos.x);
    res = rotateY(res.first, res.second, pos.y);
    res = rotateZ(res.first, res.second, pos.z);
    it = res.second;
    return [obj, it](const math::Vec3d& p) { return obj(it * p); };
  }
  inline std::function<double(const math::Vec3d&)> Scale(
      std::function<double(const math::Vec3d&)> obj, double s) {
    return [obj, s](const math::Vec3d& p) { return obj(p / s) * s; };
  }
  inline std::function<double(const math::Vec3d&)> Repeate(
      std::function<double(const math::Vec3d&)> obj, math::Vec3d c) {
    return [obj, c](const math::Vec3d& p) {
      math::Vec3d q(math::mod(p, c) - c * 0.5);
      return obj(q);
    };
  }
  inline std::function<double(const math::Vec3d&)> Displacement(
      std::function<double(const math::Vec3d&)> obj,
      std::function<double(const math::Vec3d&)> disp) {
    return [obj, disp](const math::Vec3d& p) {
      double d1 = obj(p);
      double d2 = disp(p);
      return d1 + d2;
    };
  }
  inline std::function<double(const math::Vec3d&)> Twist(
      std::function<double(const math::Vec3d&)> obj, double twist) {
    return [obj, twist](const math::Vec3d& p) {
      math::Vec2d cs(std::cos(twist * p.y), std::sin(twist * p.y));
      math::Mat2d m(cs.x, -cs.y, cs.y, cs.x);
      math::Vec3d q(m * p.xz(), p.y);
      return obj(q);
    };
  }

}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_DISTANCE_ESTIMATOR_HPP_
