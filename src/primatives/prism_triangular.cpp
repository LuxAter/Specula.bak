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
}
