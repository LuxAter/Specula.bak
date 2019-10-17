#ifndef SPECULA_GEOMETRY_INTERSECT_HPP_
#define SPECULA_GEOMETRY_INTERSECT_HPP_

namespace specula {
  class intersect {
    public:
      int obj_index;
      float t;
      glm::vec3 n;
  };
} // namespace specula

#endif  // SPECULA_GEOMETRY_INTERSECT_HPP_
