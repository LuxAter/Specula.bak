#ifndef SPECULA_OBJECT_HPP_
#define SPECULA_OBJECT_HPP_

#include <memory>

#include "basic/matrix.hpp"
#include "basic/vector.hpp"

#include "material.hpp"

namespace specula {

struct IntersectData;

class Object {
 public:
  Object();
  Object(Material mat);
  ~Object();

  void Translate(double x, double y, double z);
  void Rotate(double x, double y, double z);
  void Scale(double x, double y, double z);

  virtual bool Intersect(const estl::base::Vec3d& start,
                         const estl::base::Vec3d& dir, IntersectData& inter);

 protected:
  Material mat_;
  estl::base::Mat4d matrix_, inv_;
};

struct IntersectData {
  double near = INFINITY;
  Material mat;
  estl::base::Vec3d normal;
  estl::base::Vec3d point;
  const Object* obj;
};
}  // namespace specula

#endif  // SPECULA_OBJECT_HPP_
