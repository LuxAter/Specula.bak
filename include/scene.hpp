#ifndef SPECULA_SCENE_HPP_
#define SPECULA_SCENE_HPP_

#include "math.hpp"

namespace specula {
extern float fov;
extern glm::vec3 camera_pos, camera_center, camera_up;

void set_camera_fov(const float &v);
void set_camera_pos(const glm::vec3 &p);
void set_camera_pos(const float &x, const float &y, const float &z);
void set_camera_center(const glm::vec3 &c);
void set_camera_center(const float &x, const float &y, const float &z);
void set_camera_up(const glm::vec3 &up);
void set_camera_up(const float &x, const float &y, const float &z);
} // namespace specula

#endif // SPECULA_SCENE_HPP_
