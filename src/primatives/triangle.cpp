#include "specula/primatives/triangle.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::Triangle::Triangle(const float &x1, const float &y1, const float &z1,
                            const float &x2, const float &y2, const float &z2,
                            const float &x3, const float &y3, const float &z3)
    : Primative([this](const glm::vec3 &p) {
        auto dot2 = [](const glm::vec3 &a) { return glm::dot(a, a); };
        glm::vec3 ba = this->b_ - this->a_, pa = p - this->a_,
                  cb = this->c_ - this->b_, pb = p - this->b_,
                  ac = this->a_ - this->c_, pc = p - this->c_;
        glm::vec3 nor = glm::cross(ba, ac);

        return glm::sqrt(
            (glm::sign(glm::dot(glm::cross(ba, nor), pa)) +
                 glm::sign(glm::dot(glm::cross(cb, nor), pb)) +
                 glm::sign(glm::dot(glm::cross(ac, nor), pc)) <
             2.0f)
                ? glm::min(
                      glm::min(dot2(ba * glm::clamp(glm::dot(ba, pa) / dot2(ba),
                                                    0.0f, 1.0f) -
                                    pa),
                               dot2(cb * glm::clamp(glm::dot(cb, pb) / dot2(cb),
                                                    0.0f, 1.0f) -
                                    pb)),
                      dot2(ac * glm::clamp(glm::dot(ac, pc) / dot2(ac), 0.0f,
                                           1.0f) -
                           pc))
                : glm::dot(nor, pa) * glm::dot(nor, pa) / glm::dot(nor, nor));
      }),
      a_(x1, y1, z1), b_(x2, y2, z2), c_(x3, y3, z3) {}
