#include "specula/primatives/primative.hpp"

#include <functional>
#include <iostream>

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "specula/log.hpp"
#include "specula/uuid.hpp"
#include "specula/variant.hpp"

specula::Primative::Primative()
    : distance_([](const glm::vec3 &) {
        return std::numeric_limits<float>::infinity();
      }),
      obj_(1.0), inv_(1.0), id_(uuid::uuid()), source_("return INFINITY;") {}
specula::Primative::Primative(const std::function<float(const glm::vec3 &)> &de)
    : distance_(de), obj_(1.0), inv_(1.0), id_(uuid::uuid()),
      source_("return INFINITY;") {}
specula::Primative::Primative(const glm::mat4 &obj, const glm::mat4 &inv)
    : distance_([](const glm::vec3 &) {
        return std::numeric_limits<float>::infinity();
      }),
      obj_(obj), inv_(inv), id_(uuid::uuid()), source_("return INFINITY;") {}

std::string specula::Primative::gen_function() const {
  std::string source = fmt::format_len(
      "float de_%s(const float3 point) { float3 p = "
      "(float3)(%ff*point.x+%ff*point.y+%ff*point.z+%ff, "
      "%ff*point.x+%ff*point.y+%ff*point.z+%ff,%ff*point.x+%ff*point.y+%ff*"
      "point.z+%ff);\n %s }",
      source_.size() + id_.size() + 120, id_.c_str(), inv_[0][0], inv_[0][1],
      inv_[0][2], inv_[0][3], inv_[1][0], inv_[1][1], inv_[1][2], inv_[1][3],
      inv_[2][0], inv_[2][1], inv_[2][2], inv_[2][3], source_.c_str());
  std::string res;
  for (std::size_t i = 0; i < source.size(); ++i) {
    if (i < source.size() - 5 && source[i] == '{' && source[i + 1] == '{') {
      std::string param;
      i += 2;
      while (i < source.size()) {
        if (i < source.size() - 2 && source[i] == '}' && source[i + 1] == '}')
          break;
        else
          param += source[i];
        i++;
      }
      i++;
      typename std::map<std::string, variant<float *, glm::vec2 *, glm::vec3 *,
                                             glm::vec4 *>>::const_iterator it;
      if ((it = params_.find(param)) != params_.end()) {
        res += visit(
            [](auto &&arg) -> std::string {
              using _T = std::decay_t<decltype(arg)>;
              if constexpr (std::is_same<_T, float *>::value)
                return std::to_string(*arg) + 'f';
              else if constexpr (std::is_same<_T, glm::vec2 *>::value)
                return "(float2)(" + std::to_string(arg->x) + ',' +
                       std::to_string(arg->y) + ')';
              else if constexpr (std::is_same<_T, glm::vec3 *>::value)
                return "(float3)(" + std::to_string(arg->x) + ',' +
                       std::to_string(arg->y) + ',' + std::to_string(arg->z) +
                       ')';
              else if constexpr (std::is_same<_T, glm::vec4 *>::value)
                return "(float4)(" + std::to_string(arg->x) + ',' +
                       std::to_string(arg->y) + ',' + std::to_string(arg->z) +
                       ',' + std::to_string(arg->w) + ')';
              else
                return "";
            },
            it->second);
      } else {
        lerror("Corrupt source string, %s", source.c_str());
        lerror("\"%s\" not found in paramater map", param.c_str());
      }
    } else {
      res += source[i];
    }
  }
  return res;
}

void specula::Primative::rotate_x(const float &angle) {
  obj_ = glm::rotate(obj_, angle, glm::vec3(1.0, 0.0, 0.0));
  inv_ = glm::rotate(inv_, -angle, glm::vec3(1.0, 0.0, 0.0));
}
void specula::Primative::rotate_y(const float &angle) {
  obj_ = glm::rotate(obj_, angle, glm::vec3(0.0, 1.0, 0.0));
  inv_ = glm::rotate(inv_, -angle, glm::vec3(0.0, 1.0, 0.0));
}
void specula::Primative::rotate_z(const float &angle) {
  obj_ = glm::rotate(obj_, angle, glm::vec3(0.0, 0.0, 1.0));
  inv_ = glm::rotate(inv_, -angle, glm::vec3(0.0, 0.0, 1.0));
}
void specula::Primative::rotate_xy(const float &x, const float &y) {
  rotate_x(x);
  rotate_y(y);
}
void specula::Primative::rotate_xy(const glm::vec2 &a) {
  rotate_x(a.x);
  rotate_y(a.y);
}
void specula::Primative::rotate_xz(const float &x, const float &z) {
  rotate_x(x);
  rotate_z(z);
}
void specula::Primative::rotate_xz(const glm::vec2 &a) {
  rotate_x(a.x);
  rotate_z(a.y);
}
void specula::Primative::rotate_yx(const float &y, const float &x) {
  rotate_y(y);
  rotate_x(x);
}
void specula::Primative::rotate_yx(const glm::vec2 &a) {
  rotate_y(a.x);
  rotate_x(a.y);
}
void specula::Primative::rotate_yz(const float &y, const float &z) {
  rotate_y(y);
  rotate_z(z);
}
void specula::Primative::rotate_yz(const glm::vec2 &a) {
  rotate_y(a.x);
  rotate_z(a.y);
}
void specula::Primative::rotate_zx(const float &z, const float &x) {
  rotate_z(z);
  rotate_x(x);
}
void specula::Primative::rotate_zx(const glm::vec2 &a) {
  rotate_z(a.x);
  rotate_x(a.y);
}
void specula::Primative::rotate_zy(const float &z, const float &y) {
  rotate_z(z);
  rotate_y(y);
}
void specula::Primative::rotate_zy(const glm::vec2 &a) {
  rotate_z(a.x);
  rotate_y(a.y);
}
void specula::Primative::rotate_xyz(const float &x, const float &y,
                                    const float &z) {
  rotate_x(x);
  rotate_y(y);
  rotate_z(z);
}
void specula::Primative::rotate_xyz(const glm::vec3 &a) {
  rotate_x(a.x);
  rotate_y(a.y);
  rotate_z(a.z);
}
void specula::Primative::rotate_xzy(const float &x, const float &z,
                                    const float &y) {
  rotate_x(x);
  rotate_z(z);
  rotate_y(y);
}
void specula::Primative::rotate_xzy(const glm::vec3 &a) {
  rotate_x(a.x);
  rotate_z(a.y);
  rotate_y(a.z);
}
void specula::Primative::rotate_yxz(const float &y, const float &x,
                                    const float &z) {
  rotate_y(y);
  rotate_x(x);
  rotate_z(z);
}
void specula::Primative::rotate_yxz(const glm::vec3 &a) {
  rotate_y(a.x);
  rotate_x(a.y);
  rotate_z(a.z);
}
void specula::Primative::rotate_yzx(const float &y, const float &z,
                                    const float &x) {
  rotate_y(y);
  rotate_z(z);
  rotate_x(x);
}
void specula::Primative::rotate_yzx(const glm::vec3 &a) {
  rotate_y(a.x);
  rotate_z(a.y);
  rotate_z(a.z);
}
void specula::Primative::rotate_zxy(const float &z, const float &x,
                                    const float &y) {
  rotate_z(z);
  rotate_x(x);
  rotate_y(y);
}
void specula::Primative::rotate_zxy(const glm::vec3 &a) {
  rotate_z(a.x);
  rotate_x(a.y);
  rotate_y(a.x);
}
void specula::Primative::rotate_zyx(const float &z, const float &y,
                                    const float &x) {
  rotate_z(z);
  rotate_y(y);
  rotate_x(x);
}
void specula::Primative::rotate_zyx(const glm::vec3 &a) {
  rotate_z(a.x);
  rotate_y(a.y);
  rotate_x(a.z);
}

void specula::Primative::rotate(const float &angle, const glm::vec3 &axis) {
  obj_ = glm::rotate(obj_, angle, axis);
  inv_ = glm::rotate(inv_, -angle, axis);
}

void specula::Primative::scale(const float &x, const float &y, const float &z) {
  obj_ = glm::scale(obj_, glm::vec3(x, y, z));
  inv_ = glm::scale(inv_, glm::vec3(1.0 / x, 1.0 / y, 1.0 / z));
}
void specula::Primative::scale(const glm::vec3 &s) {
  obj_ = glm::scale(obj_, s);
  inv_ = glm::scale(inv_, glm::vec3(1.0 / s.x, 1.0 / s.y, 1.0 / s.z));
}

void specula::Primative::translate(const float &x, const float &y,
                                   const float &z) {
  obj_ = glm::translate(obj_, glm::vec3(x, y, z));
  inv_ = glm::translate(inv_, glm::vec3(-x, -y, -z));
}
void specula::Primative::translate(const glm::vec3 &t) {
  obj_ = glm::translate(obj_, t);
  inv_ = glm::translate(inv_, -t);
}
