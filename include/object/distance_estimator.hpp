#ifndef SPECULA_OBJECT_DISTANCE_ESTIMATOR_HPP_
#define SPECULA_OBJECT_DISTANCE_ESTIMATOR_HPP_

#include <functional>

#include "../math/math.hpp"

namespace specula {
namespace object {
  inline std::function<double(const math::vec3<double>&)> Sphere(
      double radius) {
    return [radius](const math::vec3<double>& p) -> double {
      return math::length(p) - radius;
    };
  }
  inline std::function<double(const math::vec3<double>&)> Box(
      math::vec3<double> box) {
    return [box](const math::vec3<double>& p) -> double {
      math::vec3<double> d = math::abs(p) - box;
      return math::length(math::max(d, 0.0)) +
             math::min(math::max(d.x, math::max(d.y, d.z)), 0.0);
    };
  }
  inline std::function<double(const math::vec3<double>&)> RoundedBox(
      math::vec3<double> box, double radius) {
    return [box, radius](const math::vec3<double>& p) -> double {
      math::vec3<double> d = math::abs(p) - box;
      return math::length(math::max(d, 0.0)) - radius +
             math::min(math::max(d.x, math::max(d.y, d.z)), 0.0);
    };
  }
  // {ring radius, radius of torus}
  inline std::function<double(const math::vec3<double>&)> Torus(double radius,
                                                                double width) {
    return [radius, width](const math::vec3<double>& p) -> double {
      math::vec2<double> q(math::length(p.xz()) - radius, p.y);
      return math::length(q) - width;
    };
  }
  inline std::function<double(const math::vec3<double>&)> Cylinder(
      math::vec3<double> cylinder) {
    return [cylinder](const math::vec3<double>& p) -> double {
      return math::length(p.xz() - cylinder.xy()) - cylinder.z;
    };
  }
  // Cone must be normalized
  inline std::function<double(const math::vec3<double>&)> Cone(
      math::vec2<double> cone) {
    return [cone](const math::vec3<double>& p) -> double {
      double q = math::length(p.xy());
      return math::dot(cone, math::vec2<double>(q, p.z));
    };
  }
  // plane must be normalized
  inline std::function<double(const math::vec3<double>&)> Plane(
      math::vec4<double> plane) {
    return [plane](const math::vec3<double>& p) -> double {
      return math::dot(p, plane.xyz()) + plane.w;
    };
  }
  inline std::function<double(const math::vec3<double>&)> HexPrism(
      math::vec2<double> hex_prism) {
    return [hex_prism](const math::vec3<double>& p) -> double {
      const math::vec3<double> k(-0.8660254, 0.5, 0.57735);
      math::vec3<double> pp = math::abs(p);
      pp.x -= 2.0 * math::min(math::dot(k.xy(), p.xy()), 0.0) * k.x;
      pp.y -= 2.0 * math::min(math::dot(k.xy(), p.xy()), 0.0) * k.y;
      math::vec2<double> d(
          math::length(p.xy() -
                       math::vec2<double>(math::clamp(p.x, -k.z * hex_prism.x,
                                                      k.z * hex_prism.x),
                                          hex_prism.x)) *
              math::sign(p.y - hex_prism.x),
          p.z - hex_prism.y);
      return math::min(math::max(d.x, d.y), 0.0) +
             math::length(math::max(d, 0.0));
    };
  }
  inline std::function<double(const math::vec3<double>&)> TriPrism(
      math::vec2<double> tri_prism) {
    return [tri_prism](const math::vec3<double>& p) -> double {
      math::vec3<double> q = math::abs(p);
      return math::max(
          q.z - tri_prism.y,
          math::max(q.x * 0.866025 + p.y * 0.5, -p.y) - tri_prism.x * 0.5);
    };
  }
  // inline std::function<double(const math::vec3<double>&)>
  // Line(math::vec3<double> a,
  //                                                      math::vec3<double> b,
  //                                                      double radius) {
  //   return [a, b, radius](const math::vec3<double>& p) -> double {
  //     math::vec3<double> pa = p - a, ba = b - a;
  //     double h = math::clamp(math::dot(pa, ba) / math::dot(ba, ba),
  //     0.0, 1.0); return math::length(pa - ba * h) - radius;
  //   };
  // }
  inline std::function<double(const math::vec3<double>&)> VerticalLine(
      double height, double radius) {
    return [height, radius](const math::vec3<double>& p) -> double {
      math::vec3<double> q(p.x, p.y - math::clamp(p.y, 0.0, height), p.z);
      return math::length(q) - radius;
    };
  }
  inline std::function<double(const math::vec3<double>&)> CappedCylinder(
      math::vec2<double> cylinder) {
    return [cylinder](const math::vec3<double>& p) -> double {
      math::vec2<double> d =
          math::abs(math::vec2<double>(math::length(p.xz()), p.y)) - cylinder;
      return math::min(math::max(d.x, d.y), 0.0) +
             math::length(math::max(d, 0.0));
    };
  }
  inline std::function<double(const math::vec3<double>&)> RoundedCylinder(
      double ra, double rb, double h) {
    return [ra, rb, h](const math::vec3<double>& p) -> double {
      math::vec2<double> d(math::length(p.xz()) - 2.0 * ra + rb,
                           math::abs(p.y) - h);
      return math::min(math::max(d.x, d.y), 0.0) +
             math::length(math::max(d, 0.0)) - rb;
    };
  }
  inline std::function<double(const math::vec3<double>&)> CappedCone(
      double h, double r1, double r2) {
    return [h, r1, r2](const math::vec3<double>& p) -> double {
      math::vec2<double> q(math::length(p.xz()), p.y);
      math::vec2<double> k1(r2, h), k2(r2 - r1, 2.0 * h),
          ca(q.x - math::min(q.x, (q.y < 0.0) ? r1 : r2), math::abs(q.y) - h),
          cb(q - k1 +
             k2 * math::clamp(math::dot(k1 - q, k2) / math::dot(k2, k2), 0.0,
                              1.0));
      double s = (cb.x < 0.0 && ca.y < 0.0) ? -1.0 : 1.0;
      return s * math::sqrt(math::min(math::dot(ca, ca), math::dot(cb, cb)));
    };
  }
  inline std::function<double(const math::vec3<double>&)> RoundedCone(
      double h, double r1, double r2) {
    return [h, r1, r2](const math::vec3<double>& p) -> double {
      math::vec2<double> q(math::length(p.xz()), p.y);
      double b = (r1 - r2) / h;
      double a = math::sqrt(1.0 - b * b);
      double k = math::dot(q, math::vec2<double>(-b, a));
      if (k < 0.0) return math::length(q) - r1;
      if (k > a * h) return math::length(q - math::vec2<double>(0.0, h)) - r2;
      return math::dot(q, math::vec2<double>(a, b)) - r1;
    };
  }
  inline std::function<double(const math::vec3<double>&)> Ellipsoid(
      math::vec3<double> r) {
    return [r](const math::vec3<double>& p) -> double {
      double k0 = math::length(p / r);
      double k1 = math::length(p / (r * r));
      return k0 * (k0 - 1.0) / k1;
    };
  }
  inline std::function<double(const math::vec3<double>&)> Triangle(
      math::vec3<double> a, math::vec3<double> b, math::vec3<double> c) {
    return [a, b, c](const math::vec3<double>& p) -> double {
      math::vec3<double> ba = b - a, pa = p - a, cb = c - b, pb = p - b,
                         ac = a - c, pc = p - c;
      math::vec3<double> nor = math::cross(ba, ac);
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
  inline std::function<double(const math::vec3<double>&)> Quad(
      math::vec3<double> a, math::vec3<double> b, math::vec3<double> c,
      math::vec3<double> d) {
    return [a, b, c, d](const math::vec3<double>& p) -> double {
      math::vec3<double> ba = b - a, pa = p - a, cb = c - b, pb = p - b,
                         dc = d - c, pc = p - c, ad = a - d, pd = p - d;
      math::vec3<double> nor = math::cross(ba, ad);
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

  inline std::function<double(const math::vec3<double>&)> Streach(
      std::function<double(const math::vec3<double>&)> obj,
      math::vec3<double> h) {
    return [obj, h](const math::vec3<double>& p) -> double {
      math::vec3<double> q = math::abs(p) - h;
      return obj(math::max(q, 0.0)) +
             math::min(math::max(q.x, math::max(q.y, q.z)), 0.0);
    };
  }
  inline std::function<double(const math::vec3<double>&)> Round(
      std::function<double(const math::vec3<double>&)> obj, double radius) {
    return [obj, radius](const math::vec3<double>& p) -> double {
      return obj(p) - radius;
    };
  }
  inline std::function<double(const math::vec3<double>&)> Onion(
      std::function<double(const math::vec3<double>&)> obj, double thickness) {
    return [obj, thickness](const math::vec3<double>& p) -> double {
      return math::abs(obj(p)) - thickness;
    };
  }

  inline std::function<double(const math::vec3<double>&)> Union(
      std::function<double(const math::vec3<double>&)> obj1,
      std::function<double(const math::vec3<double>&)> obj2) {
    return [obj1, obj2](const math::vec3<double>& p) -> double {
      return math::min(obj1(p), obj2(p));
    };
  }
  inline std::function<double(const math::vec3<double>&)> Subtraction(
      std::function<double(const math::vec3<double>&)> obj1,
      std::function<double(const math::vec3<double>&)> obj2) {
    return [obj1, obj2](const math::vec3<double>& p) -> double {
      return math::max(-obj1(p), obj2(p));
    };
  }
  inline std::function<double(const math::vec3<double>&)> Intersection(
      std::function<double(const math::vec3<double>&)> obj1,
      std::function<double(const math::vec3<double>&)> obj2) {
    return [obj1, obj2](const math::vec3<double>& p) -> double {
      return math::max(obj1(p), obj2(p));
    };
  }

  inline std::function<double(const math::vec3<double>&)> SmoothUnion(
      std::function<double(const math::vec3<double>&)> obj1,
      std::function<double(const math::vec3<double>&)> obj2, double k) {
    return [obj1, obj2, k](const math::vec3<double>& p) -> double {
      double d1 = obj1(p), d2 = obj2(p);
      double h = math::clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0);
      return math::mix(d2, d1, h) - k * h * (1.0 - h);
    };
  }
  inline std::function<double(const math::vec3<double>&)> SmoothSubtraction(
      std::function<double(const math::vec3<double>&)> obj1,
      std::function<double(const math::vec3<double>&)> obj2, double k) {
    return [obj1, obj2, k](const math::vec3<double>& p) -> double {
      double d1 = obj1(p), d2 = obj2(p);
      double h = math::clamp(0.5 - 0.5 * (d2 + d1) / k, 0.0, 1.0);
      return math::mix(d2, -d1, h) + k * h * (1.0 - h);
    };
  }
  inline std::function<double(const math::vec3<double>&)> SmoothIntersection(
      std::function<double(const math::vec3<double>&)> obj1,
      std::function<double(const math::vec3<double>&)> obj2, double k) {
    return [obj1, obj2, k](const math::vec3<double>& p) -> double {
      double d1 = obj1(p), d2 = obj2(p);
      double h = math::clamp(0.5 - 0.5 * (d2 - d1) / k, 0.0, 1.0);
      return math::mix(d2, d1, h) + k * h * (1.0 - h);
    };
  }
  inline std::function<double(const math::vec3<double>&)> Translate(
      std::function<double(const math::vec3<double>&)> obj,
      math::vec3<double> pos) {
    math::mat4<double> t(1), it(1);
    math::translate(t, it, pos);
    return [obj, it](const math::vec3<double>& p) -> double {
      return obj(it * p);
    };
  }
  inline std::function<double(const math::vec3<double>&)> Rotate(
      std::function<double(const math::vec3<double>&)> obj,
      math::vec3<double> pos) {
    math::mat4<double> t(1), it(1);
    rotateX(t, it, pos.x);
    rotateY(t, it, pos.y);
    rotateZ(t, it, pos.z);
    return [obj, it](const math::vec3<double>& p) -> double {
      return obj(it * p);
    };
  }
  inline std::function<double(const math::vec3<double>&)> Scale(
      std::function<double(const math::vec3<double>&)> obj, double s) {
    return [obj, s](const math::vec3<double>& p) -> double {
      return obj(p / s) * s;
    };
  }
  inline std::function<double(const math::vec3<double>&)> Repeate(
      std::function<double(const math::vec3<double>&)> obj,
      math::vec3<double> c) {
    return [obj, c](const math::vec3<double>& p) -> double {
      math::vec3<double> q(math::mod(p, c) - c * 0.5);
      return obj(q);
    };
  }
  inline std::function<double(const math::vec3<double>&)> Displacement(
      std::function<double(const math::vec3<double>&)> obj,
      std::function<double(const math::vec3<double>&)> disp) {
    return [obj, disp](const math::vec3<double>& p) -> double {
      double d1 = obj(p);
      double d2 = disp(p);
      return d1 + d2;
    };
  }
  inline std::function<double(const math::vec3<double>&)> Twist(
      std::function<double(const math::vec3<double>&)> obj, double twist) {
    return [obj, twist](const math::vec3<double>& p) -> double {
      math::vec2<double> cs(std::cos(twist * p.y), std::sin(twist * p.y));
      math::mat2 m(cs.x, -cs.y, cs.y, cs.x);
      math::vec3<double> q(m * p.xz(), p.y);
      return obj(q);
    };
  }

}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_DISTANCE_ESTIMATOR_HPP_
