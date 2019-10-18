#include "specula/primatives/quad.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::Quad::Quad(const float &x1, const float &y1, const float &z1,
                    const float &x2, const float &y2, const float &z2,
                    const float &x3, const float &y3, const float &z3,
                    const float &x4, const float &y4, const float &z4)
    : Primative([this](const glm::vec3 &p) {
        auto dot2 = [](const glm::vec3 &a) { return glm::dot(a, a); };
        glm::vec3 ba = this->b_ - this->a_, pa = p - this->a_,
                  cb = this->c_ - this->b_, pb = p - this->b_,
                  dc = this->d_ - this->c_, pc = p - this->c_,
                  ad = this->a_ - this->d_, pd = p - this->d_;
        glm::vec3 nor = glm::cross(ba, ad);

        return glm::sqrt(
            (glm::sign(glm::dot(glm::cross(ba, nor), pa)) +
                 glm::sign(glm::dot(glm::cross(cb, nor), pb)) +
                 glm::sign(glm::dot(glm::cross(dc, nor), pc)) +
                 glm::sign(glm::dot(glm::cross(ad, nor), pd)) <
             3.0f)
                ? glm::min(
                      glm::min(
                          glm::min(
                              dot2(ba * glm::clamp(glm::dot(ba, pa) / dot2(ba),
                                                   0.0f, 1.0f) -
                                   pa),
                              dot2(cb * glm::clamp(glm::dot(cb, pb) / dot2(cb),
                                                   0.0f, 1.0f) -
                                   pb)),
                          dot2(dc * glm::clamp(glm::dot(dc, pc) / dot2(dc),
                                               0.0f, 1.0f) -
                               pc)),
                      dot2(ad * glm::clamp(glm::dot(ad, pd) / dot2(ad), 0.0f,
                                           1.0f) -
                           pd))
                : glm::dot(nor, pa) * glm::dot(nor, pa) / dot2(nor));
      }),
      a_(x1, y1, z1), b_(x2, y2, z2), c_(x3, y3, z3), d_(x4, y4, z4) {}
