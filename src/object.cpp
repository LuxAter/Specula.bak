#include "object.hpp"

#include <memory>

#include "basic/matrix.hpp"
#include "basic/vector.hpp"

#include "material.hpp"

specula::Object::Object() {
  matrix_.Diagonal(1);
  inv_.Diagonal(1);
}
specula::Object::Object(Material mat):mat_(mat) {
  matrix_.Diagonal(1);
  inv_.Diagonal(1);
}
specula::Object::~Object() {}

void specula::Object::Translate(double x, double y, double z) {}
void specula::Object::Rotate(double x, double y, double z) {}
void specula::Object::Scale(double x, double y, double z) {}

bool specula::Object::Intersect(const estl::base::Vec3d& start,
                                const estl::base::Vec3d& dir,
                                IntersectData& inter) {
  return false;
}
