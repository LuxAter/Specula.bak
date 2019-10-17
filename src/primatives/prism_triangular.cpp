#include "specula/primatives/prism_triangular.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::TriangularPrism::TriangularPrism(const float &a, const float &b)
    : Primative([this](const glm::vec3 &p) {
        glm::vec3 q(glm::abs(p));
        return glm::max(q.z - this->b_,
                        glm::max(q.x * 0.866025f + p.y * 0.5f, -p.y) -
                            this->a_ * 0.5f);
      }),
      a_(a), b_(b) {
  this->source_ =
      fmt::format("float3 q = fabs(p); return "
                  "max(q.z-{{%1$s-triangular-prism.b}},max(q.x*0.866025f+p.y*0."
                  "5f, -p.y) - {{%1$s-triangular-prism.a}}*0.5f);",
                  this->id_.c_str());
  this->params_[fmt::format("%s-triangular-prism.a", this->id_.c_str())] = &a_;
  this->params_[fmt::format("%s-triangular-prism.b", this->id_.c_str())] = &a_;
}
