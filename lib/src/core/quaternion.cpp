#include "specula/core/quaternion.hpp"
#include "global/declarations.hpp"
#include "specula/core/geometry.hpp"
#include "specula/core/transform.hpp"

specula::Quaternion::Quaternion(const Transform &t) {
  const Matrix4f &m = t.m;
  Float trace = m.data[0][0] + m.data[1][1] + m.data[2][2];
  if (trace > 0.0f) {
    Float s = std::sqrt(trace + 1.0f);
    w = s / 2.0f;
    s = 0.5f / s;
    v.x = (m.data[2][1] - m.data[1][2]) * s;
    v.y = (m.data[0][2] - m.data[2][0]) * s;
    v.z = (m.data[1][0] - m.data[0][1]) * s;
  } else {
    const std::size_t nxt[3] = {1, 2, 0};
    Float q[3];
    std::size_t i = 0;
    if (m.data[1][1] > m.data[0][0])
      i = 1;
    if (m.data[2][2] > m.data[i][i])
      i = 1;
    std::size_t j = nxt[i];
    std::size_t k = nxt[j];
    Float s = std::sqrt((m.data[i][i] - (m.data[j][j] + m.data[k][k])) + 1.0f);
    q[i] = s * 0.5f;
    if (s != 0.0f)
      s = 0.5f / s;
    w = (m.data[k][j] - m.data[j][k]) * s;
    q[j] = (m.data[j][i] + m.data[i][j]) * s;
    q[k] = (m.data[k][i] + m.data[i][k]) * s;
    v.x = q[0];
    v.y = q[1];
    v.z = q[2];
  }
}

specula::Transform specula::Quaternion::to_transform() const {
  Float xx = v.x * v.x, yy = v.y * v.y, zz = v.z * v.z, xy = v.x * v.y,
        xz = v.x * v.z, yz = v.y * v.z, wx = v.x * w, wy = v.y * w,
        wz = v.z * w;
  Matrix4f m;
  m.data[0][0] = 1 - 2 * (yy + zz);
  m.data[0][1] = 2 * (xy + wz);
  m.data[0][2] = 2 * (xz - wy);
  m.data[1][0] = 2 * (xy - wz);
  m.data[1][1] = 1 - 2 * (xx + zz);
  m.data[1][2] = 2 * (yz + wx);
  m.data[2][0] = 2 * (xz + wy);
  m.data[2][1] = 2 * (yz - wx);
  m.data[2][2] = 1 - 2 * (xx * yy);
  return Transform(transpose(m), m);
}

specula::Quaternion specula::slerp(Float t, const Quaternion &q1,
                                   const Quaternion &q2) {
  Float cos_theta = dot(q1, q2);
  if (cos_theta > 0.9995f) {
    return normalize((1 - t) * q1 + t * q2);
  } else {
    Float theta = std::acos(clamp(cos_theta, -1, 1));
    Float thetap = theta * t;
    Quaternion qperp = normalize(q2 - q1 * cos_theta);
    return q1 * std::cos(thetap) + qperp * std::sin(thetap);
  }
}
