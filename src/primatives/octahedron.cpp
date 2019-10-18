#define GLM_FORCE_SWIZZLE
#include "specula/primatives/octahedron.hpp"

#include "specula/primatives/primative.hpp"

#include <functional>

#include <glm/glm.hpp>

#include "specula/fmt.hpp"
#include "specula/log.hpp"

specula::Octahedron::Octahedron(const float &r)
    : Primative([this](const glm::vec3 &p) {
        glm::vec3 pt = glm::abs(p);
        float m = pt.x + pt.y + pt.z - this->radius_;
        glm::vec3 q;
        if (3.0f * pt.x < m)
          q = pt.xyz();
        else if (3.0f * pt.y < m)
          q = pt.yzx();
        else if (3.0f * pt.z < m)
          q = pt.zxy();
        else
          return m * 0.57735027f;
        float k =
            glm::clamp(0.5f * (q.z - q.y + this->radius_), 0.0f, this->radius_);
        return glm::length(glm::vec3(q.x, q.y - this->radius_ + k, q.z - k));
      }),
      radius_(r) {}
