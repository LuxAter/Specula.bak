#ifndef SPECULA_OBJECT_DISTANCE_ESTIMATOR_HPP_
#define SPECULA_OBJECT_DISTANCE_ESTIMATOR_HPP_

#include <functional>

#include "../math/math.hpp"

namespace specula {
namespace object {
  inline std::function<double(const math::vec3&)> Sphere(double radius) {
    return [radius](const math::vec3& p) -> double {
      return math::length(p) - radius;
    };
  }
  inline std::function<double(const math::vec3&)> Box(math::vec3 box) {
    return [box](const math::vec3& p) -> double {
      math::vec3 d = math::abs(p) - box;
      return math::length(math::max(d, 0.0)) +
             math::min(math::max(d[0], math::max(d[1], d[2])), 0.0);
    };
  }
  inline std::function<double(const math::vec3&)> RoundedBox(math::vec3 box,
                                                             double radius) {
    return [box, radius](const math::vec3& p) -> double {
      math::vec3 d = math::abs(p) - box;
      return math::length(math::max(d, 0.0)) - radius +
             math::min(math::max(d[0], math::max(d[1], d[2])), 0.0);
    };
  }
  // {ring radius, radius of torus}
  inline std::function<double(const math::vec3&)> Torus(math::vec2 torus) {
    return [torus](const math::vec3& p) -> double {
      math::vec2 q(math::length(p.xz()) - torus[0], p[1]);
      return math::length(q) - torus[1];
    };
  }
  inline std::function<double(const math::vec3&)> Cylinder(
      math::vec3 cylinder) {
    return [cylinder](const math::vec3& p) -> double {
      return math::length(p.xz() - cylinder.xy()) - cylinder[2];
    };
  }
  // Cone must be normalized
  inline std::function<double(const math::vec3&)> Cone(math::vec2 cone) {
    return [cone](const math::vec3& p) {
      double q = math::length(p.xy());
      return math::dot(cone, math::vec2(q, p[2]));
    };
  }
  // plane must be normalized
  inline std::function<double(const math::vec3&)> Plane(math::vec4 plane) {
    return [plane](const math::vec3& p) {
      return math::dot(p, plane.xyz()) + plane[3];
    };
  }
  inline std::function<double(const math::vec3&)> HexPrism(
      math::vec2 hex_prism) {
    return [hex_prism](const math::vec3& p) {
      const math::vec3 k(-0.8660254, 0.5, 0.57735);
      math::vec3 pp = math::abs(p);
      pp[0] -= 2.0 * math::min(math::dot(k.xy(), p.xy()), 0.0) * k[0];
      pp[1] -= 2.0 * math::min(math::dot(k.xy(), p.xy()), 0.0) * k[1];
      math::vec2 d(
          math::length(p.xy() -
                       math::vec2(math::clamp(p[0], -k[2] * hex_prism[0],
                                              k[2] * hex_prism[0]),
                                  hex_prism[0])) *
              math::sign(p[1] - hex_prism[0]),
          p[2] - hex_prism[1]);
      return math::min(math::max(d[0], d[1]), 0.0) +
             math::length(math::max(d, 0.0));
    };
  }
  inline std::function<double(const math::vec3&)> TriPrism(
      math::vec2 tri_prism) {
    return [tri_prism](const math::vec3& p) {
      math::vec3 q = math::abs(p);
      return math::max(
          q[2] - tri_prism[1],
          math::max(q[0] * 0.866025 + p[1] * 0.5, -p[1]) - tri_prism[0] *
          0.5);
    };
  }
  // inline std::function<double(const math::vec3&)> Line(math::vec3 a,
  //                                                      math::vec3 b,
  //                                                      double radius) {
  //   return [a, b, radius](const math::vec3& p) {
  //     math::vec3 pa = p - a, ba = b - a;
  //     double h = math::clamp(math::dot(pa, ba) / math::dot(ba, ba),
  //     0.0, 1.0); return math::length(pa - ba * h) - radius;
  //   };
  // }
  inline std::function<double(const math::vec3&)> VerticalLine(double height,
                                                               double radius)
                                                               {
    return [height, radius](const math::vec3& p) {
      math::vec3 q(p[0], p[1] - math::clamp(p[1], 0.0, height), p[2]);
      return math::length(q) - radius;
    };
  }
  inline std::function<double(const math::vec3&)> CappedCylinder(
      math::vec2 cylinder) {
    return [cylinder](const math::vec3& p) {
      math::vec2 d =
          math::abs(math::vec2(math::length(p.xz()), p[1])) - cylinder;
      return math::min(math::max(d[0], d[1]), 0.0) +
             math::length(math::max(d, 0.0));
    };
  }
  inline std::function<double(const math::vec3&)> RoundedCylinder(double ra,
                                                                  double rb,
                                                                  double h) {
    return [ra, rb, h](const math::vec3& p) {
      math::vec2 d(math::length(p.xz()) - 2.0 * ra + rb, math::abs(p[1]) -
      h); return math::min(math::max(d[0], d[1]), 0.0) +
             math::length(math::max(d, 0.0)) - rb;
    };
  }
  inline std::function<double(const math::vec3&)> CappedCone(double h,
                                                             double r1,
                                                             double r2) {
    return [h, r1, r2](const math::vec3& p) {
      math::vec2 q(math::length(p.xz()), p[1]);
      math::vec2 k1(r2, h), k2(r2 - r1, 2.0 * h),
          ca(q[0] - math::min(q[0], (q[1] < 0.0) ? r1 : r2),
             math::abs(q[1]) - h),
          cb(q - k1 +
             k2 * math::clamp(math::dot(k1 - q, k2) / math::dot(k2, k2), 0.0,
                              1.0));
      double s = (cb[0] < 0.0 && ca[1] < 0.0) ? -1.0 : 1.0;
      return s * math::sqrt(math::min(math::dot(ca, ca), math::dot(cb, cb)));
    };
  }
  inline std::function<double(const math::vec3&)> RoundedCone(double h,
                                                              double r1,
                                                              double r2) {
    return [h, r1, r2](const math::vec3& p) {
      math::vec2 q(math::length(p.xz()), p[1]);
      double b = (r1 - r2) / h;
      double a = math::sqrt(1.0 - b * b);
      double k = math::dot(q, math::vec2(-b, a));
      if (k < 0.0) return math::length(q) - r1;
      if (k > a * h) return math::length(q - math::vec2(0.0, h)) - r2;
      return math::dot(q, math::vec2(a, b)) - r1;
    };
  }
  inline std::function<double(const math::vec3&)> Ellipsoid(math::vec3 r) {
    return [r](const math::vec3& p) {
      double k0 = math::length(p / r);
      double k1 = math::length(p / (r * r));
      return k0 * (k0 - 1.0) / k1;
    };
  }
  inline std::function<double(const math::vec3&)> Triangle(math::vec3 a,
                                                           math::vec3 b,
                                                           math::vec3 c) {
    return [a, b, c](const math::vec3& p) {
      math::vec3 ba = b - a, pa = p - a, cb = c - b, pb = p - b, ac = a - c,
                 pc = p - c;
      math::vec3 nor = math::cross(ba, ac);
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
  inline std::function<double(const math::vec3&)> Quad(math::vec3 a,
                                                       math::vec3 b,
                                                       math::vec3 c,
                                                       math::vec3 d) {
    return [a, b, c, d](const math::vec3& p) {
      math::vec3 ba = b - a, pa = p - a, cb = c - b, pb = p - b, dc = d - c,
                 pc = p - c, ad = a - d, pd = p - d;
      math::vec3 nor = math::cross(ba, ad);
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
                            dc * math::clamp(math::dot(dc, pc) /
                            math::dot2(dc),
                                             0.0, 1.0) -
                            pc)),
                    math::dot2(
                        ad * math::clamp(math::dot(ad, pd) / math::dot2(ad),
                                         0.0, 1.0) -
                        pd))
              : math::dot(nor, pa) * math::dot(nor, pa) / math::dot2(nor));
    };
  }

  inline std::function<double(const math::vec3&)> Streach(
      std::function<double(const math::vec3&)> obj, math::vec3 h) {
    return [obj, h](const math::vec3& p) {
      math::vec3 q = math::abs(p) - h;
      return obj(math::max(q, 0.0)) +
             math::min(math::max(q[0], math::max(q[1], q[2])), 0.0);
    };
  }
  inline std::function<double(const math::vec3&)> Round(
      std::function<double(const math::vec3&)> obj, double radius) {
    return [obj, radius](const math::vec3& p) { return obj(p) - radius; };
  }
  inline std::function<double(const math::vec3&)> Onion(
      std::function<double(const math::vec3&)> obj, double thickness) {
    return [obj, thickness](const math::vec3& p) {
      return math::abs(obj(p)) - thickness;
    };
  }

  inline std::function<double(const math::vec3&)> Union(
      std::function<double(const math::vec3&)> obj1,
      std::function<double(const math::vec3&)> obj2) {
    return [obj1, obj2](const math::vec3& p) {
      return math::min(obj1(p), obj2(p));
    };
  }
  inline std::function<double(const math::vec3&)> Subtraction(
      std::function<double(const math::vec3&)> obj1,
      std::function<double(const math::vec3&)> obj2) {
    return [obj1, obj2](const math::vec3& p) {
      return math::max(-obj1(p), obj2(p));
    };
  }
  inline std::function<double(const math::vec3&)> Intersection(
      std::function<double(const math::vec3&)> obj1,
      std::function<double(const math::vec3&)> obj2) {
    return [obj1, obj2](const math::vec3& p) {
      return math::max(obj1(p), obj2(p));
    };
  }

  inline std::function<double(const math::vec3&)> SmoothUnion(
      std::function<double(const math::vec3&)> obj1,
      std::function<double(const math::vec3&)> obj2, double k) {
    return [obj1, obj2, k](const math::vec3& p) {
      double d1 = obj1(p), d2 = obj2(p);
      double h = math::clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0);
      return math::mix(d2, d1, h) - k * h * (1.0 - h);
    };
  }
  inline std::function<double(const math::vec3&)> SmoothSubtraction(
      std::function<double(const math::vec3&)> obj1,
      std::function<double(const math::vec3&)> obj2, double k) {
    return [obj1, obj2, k](const math::vec3& p) {
      double d1 = obj1(p), d2 = obj2(p);
      double h = math::clamp(0.5 - 0.5 * (d2 + d1) / k, 0.0, 1.0);
      return math::mix(d2, -d1, h) + k * h * (1.0 - h);
    };
  }
  inline std::function<double(const math::vec3&)> SmoothIntersection(
      std::function<double(const math::vec3&)> obj1,
      std::function<double(const math::vec3&)> obj2, double k) {
    return [obj1, obj2, k](const math::vec3& p) {
      double d1 = obj1(p), d2 = obj2(p);
      double h = math::clamp(0.5 - 0.5 * (d2 - d1) / k, 0.0, 1.0);
      return math::mix(d2, d1, h) + k * h * (1.0 - h);
    };
  }
  inline std::function<double(const math::vec3&)> Translate(
      std::function<double(const math::vec3&)> obj, math::vec3 pos) {
    math::mat4 t(1), it(1);
    math::translate(t, it, pos);
    return [obj, it](const math::vec3& p) { return obj(it * p); };
  }
  inline std::function<double(const math::vec3&)> Rotate(
      std::function<double(const math::vec3&)> obj, math::vec3 pos) {
    math::mat4 t(1), it(1);
    rotateX(t, it, pos[0]);
    rotateY(t, it, pos[1]);
    rotateZ(t, it, pos[2]);
    return [obj, it](const math::vec3& p) { return obj(it * p); };
  }
  inline std::function<double(const math::vec3&)> Scale(
      std::function<double(const math::vec3&)> obj, double s) {
    return [obj, s](const math::vec3& p) { return obj(p / s) * s; };
  }
  inline std::function<double(const math::vec3&)> Repeate(
      std::function<double(const math::vec3&)> obj, math::vec3 c) {
    return [obj, c](const math::vec3& p) {
      math::vec3 q(math::mod(p, c) - c * 0.5);
      return obj(q);
    };
  }
  inline std::function<double(const math::vec3&)> Displacement(
      std::function<double(const math::vec3&)> obj,
      std::function<double(const math::vec3&)> disp) {
    return [obj, disp](const math::vec3& p) {
      double d1 = obj(p);
      double d2 = disp(p);
      return d1 + d2;
    };
  }
  inline std::function<double(const math::vec3&)> Twist(
      std::function<double(const math::vec3&)> obj, double twist) {
    return [obj, twist](const math::vec3& p) {
      math::vec2 cs(std::cos(twist * p[1]), std::sin(twist * p[1]));
      math::mat2 m(cs[0], -cs[1], cs[1], cs[0]);
      math::vec3 q(m * p.xz(), p[1]);
      return obj(q);
    };
  }

}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_DISTANCE_ESTIMATOR_HPP_
