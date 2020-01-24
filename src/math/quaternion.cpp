#include "specula/math/quaternion.hpp"

#include "specula/global.hpp"

#include "specula/math/matrix/matrix4x4.hpp"
#include "specula/transform/transform.hpp"

specula::Quaternion::Quaternion(const Transform &t) {
  const Matrix4x4f &m = t.m;
  Float trace = m.data[0][0] + m.data[1][1] + m.data[2][2];
  if (trace > 0.f) {
    Float s = std::sqrt(trace + 1.0f);
    w = s / 2.0f;
    s = 0.5f / s;
    x = (m.data[2][1] - m.data[1][2]) * s;
    y = (m.data[0][2] - m.data[2][0]) * s;
    z = (m.data[1][0] - m.data[0][1]) * s;
  } else {
    const typename Matrix4x4f::size_type nxt[3] = {1, 2, 0};
    Float q[3];
    typename Matrix4x4f::size_type i = 0;
    if (m.data[1][1] > m.data[0][0])
      i = 1;
    if (m.data[2][2] > m.data[i][i])
      i = 2;
    typename Matrix4x4f::size_type j = nxt[i];
    typename Matrix4x4f::size_type k = nxt[j];
    Float s = std::sqrt((m.data[i][i] - (m.data[j][i] + m.data[k][k])) + 1.0f);
    q[i] = s * 0.5f;
    if (s != 0.0f)
      s = 0.5f / s;
    w = (m.data[k][j] - m.data[j][k]) * s;
    q[j] = (m.data[j][i] + m.data[i][j]) * s;
    q[k] = (m.data[k][i] + m.data[i][k]) * s;
    x = q[0];
    y = q[1];
    z = q[2];
  }
}

specula::Transform specula::Quaternion::to_transform() const {
  Float xx = x * x, yy = y * y, zz = z * z;
  Float xy = x * y, xz = x * z, yz = y * z;
  Float wx = x * w, wy = y * w, wz = z * w;
  Matrix4x4f m;
  m.data[0][0] = 1 - 2 * (yy + zz);
  m.data[0][1] = 2 * (xy + wz);
  m.data[0][2] = 2 * (xz - wy);
  m.data[1][0] = 2 * (xy - wz);
  m.data[1][1] = 1 - 2 * (xx + zz);
  m.data[1][2] = 2 * (yz + wx);
  m.data[2][0] = 2 * (xz + wy);
  m.data[2][1] = 2 * (yz - wx);
  m.data[2][2] = 1 - 2 * (xx + yy);

  return Transform(transpose(m), m);
}

specula::Quaternion specula::slerp(const Quaternion &q1, const Quaternion &q2,
                                   Float t) {
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
