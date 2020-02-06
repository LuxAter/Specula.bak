float sdfSphere(float3 p, float r) { return length(p) - r; }
float sdfBox(float3 p, float3 dims) {
  const float3 q = abs(p) - dims;
  return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0);
}
float sdfRoundBox(float3 p, float3 dims, float r) {
  const float3 q = abs(p) - b;
  return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0) - r;
}
float sdfPlane(float3 p, float4 n) { return dot(p, n.xyz) + n.w; }
float sdfHexPrisim(float3 p, float2 h) {
  const float3 k = float3(-0.8660254, 0.5, 0.57735);
  p = abs(p);
  p.xy -= 2.0 * min(dot(k.xy, p.xy), 0.0) * k.xy;
  float2 d =
      float2(length(p.xy - float2(clamp(p.x, -k.z * h.x, k.z * h.x), h.x)) *
                 sign(p.y - h.x),
             p.z - h.y);
  return min(max(d.x, d.y), 0.0) + length(max(d, 0.0));
}
float sdfTriPrism(float3 p, float2 h) {
  const float k = sqrt(3.0);
  h.x *= 0.5 * k;
  p.xy /= h.x;
  p.x = abs(p.x) - 1.0;
  p.y = p.y + 1.0 / k;
  if (p.x + k * p.y > 0.0)
    p.xy = float2(p.x - k * p.y, -k * p.x - p.y) / 2.0;
  p.x -= clamp(p.x, -2.0, 0.0);
  float d1 = length(p.xy) * sign(-p.y) * h.x;
  float d2 = abs(p.z) - h.y;
  return length(max(float2(d1, d2), 0.0)) + min(max(d1, d2), 0.);
}
float sdfCapsule(float3 p, float3 a, float3 b, float r) {
  float3 pa = p - a, ba = b - a;
  float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
  return length(pa - ba * h) - r;
}
float sdfVerticalCapsule(float3 p, float h, float r) {
  p.y -= clamp(p.y, 0.0, h);
  return length(p) - r;
}
float sdfCylinder(float3 p, float3 c) { return length(p.xz - c.xy) - c.z; }
float sdfCappedCylinder(float3 p, float h, float r) {
  float2 d = abs(float2(length(p.xz), p.y)) - float2(h, r);
  return min(max(d.x, d.y), 0.0) + length(max(d, 0.0));
}
float sdfCappedCylinder(float3 p, float3 a, float3 b, float r) {
  float3 ba = b - a;
  float3 pa = p - a;
  float baba = dot(ba, ba);
  float paba = dot(pa, ba);
  float x = length(pa * baba - ba * paba) - r * baba;
  float y = abs(paba - baba * 0.5) - baba * 0.5;
  float x2 = x * x;
  float y2 = y * y * baba;
  float d = (max(x, y) < 0.0)
                ? -min(x2, y2)
                : (((x > 0.0) ? x2 : 0.0) + ((y > 0.0) ? y2 : 0.0));
  return sign(d) * sqrt(abs(d)) / baba;
}
float sdfRoundedCylinder(float3 p, float ra, float rb, float h) {
  float2 d = float2(length(p.xz) - 2.0 * ra + rb, abs(p.y) - h);
  return min(max(d.x, d.y), 0.0) + length(max(d, 0.0)) - rb;
}
float sdfCone(float3 p, float2 c) {
  float q = length(p.xy);
  return dot(c, float2(q, p.z));
}
float sdfCappedCone(float3 p, float h, float r1, float r2) {
  float2 q = float2(length(p.xz), p.y);
  float2 k1 = float2(r2, h);
  float2 k2 = float2(r2 - r1, 2.0 * h);
  float2 ca = float2(q.x - min(q.x, (q.y < 0.0) ? r1 : r2), abs(q.y) - h);
  float2 cb = q - k1 + k2 * clamp(dot(k1 - q, k2) / dot2(k2), 0.0, 1.0);
  float s = (cb.x < 0.0 && ca.y < 0.0) ? -1.0 : 1.0;
  return s * sqrt(min(dot2(ca), dot2(cb)));
}
float sdfCappedCone(float3 p, float3 a, float3 b, float ra, float rb) {
  float rba = rb - ra;
  float baba = dot(b - a, b - a);
  float papa = dot(p - a, p - a);
  float paba = dot(p - a, b - a) / baba;
  float x = sqrt(papa - paba * paba * baba);
  float cax = max(0.0, x - ((paba < 0.5) ? ra : rb));
  float cay = abs(paba - 0.5) - 0.5;
  float k = rba * rba + baba;
  float f = clamp((rba * (x - ra) + paba * baba) / k, 0.0, 1.0);
  float cbx = x - ra - f * rba;
  float cby = paba - f;
  float s = (cbx < 0.0 && cay < 0.0) ? -1.0 : 1.0;
  return s *
         sqrt(min(cax * cax + cay * cay * baba, cbx * cbx + cby * cby * baba));
}
float sdfSolidAngle(float3 p, float2 c, float ra) {
  float2 q = float2(length(p.xz), p.y);
  float l = length(q) - ra;
  float m = length(q - c * clamp(dot(q, c), 0.0, ra));
  return max(l, m * sign(c.y * q.x - c.x * q.y));
}
float sdfRoundCone(float3 p, float r1, float r2, float h) {
  float2 q = float2(length(p.xz), p.y);
  float b = (r1 - r2) / h;
  float a = sqrt(1.0 - b * b);
  float k = dot(q, float2(-b, a));
  if (k < 0.0)
    return length(q) - r1;
  if (k > a * h)
    return length(q - float2(0.0, h)) - r2;
  return dot(q, float2(a, b)) - r1;
}
// BOUNDED
float sdfEllipsoid(float3 p, float3 r) {
  float k0 = length(p / r);
  float k1 = length(p / (r * r));
  return k0 * (k0 - 1.0) / k1;
}
float sdfTorus(float3 p, float2 t) {
  float2 q = float2(length(p.xz) - t.x, p.y);
  return length(q) - t.y;
}
float sdfdCappedTorus(float3 p, float2 sc, float ra, float rb) {
  p.x = abs(p.x);
  float k = (sc.y * p.x > sc.x * p.y) ? dot(p.xy, sc) : length(p.xy);
  return sqrt(dot(p, p) + ra * ra - 2.0 * ra * k) - rb;
}
// WEIRD
float4 sdfJoint3DSphere(float3 p, float l, float a, float w) {
  if (abs(a) < 0.001)
    return float4(length(p - float3(0, clamp(p.y, 0.0, l), 0)) - w, p);
  float2 sc = float2(sin(a), cos(a));
  float ra = 0.5 * l / a;
  p.x -= ra;
  float2 q = p.xy - 2.0 * sc * max(0.0, dot(sc, p.xy));
  float u = abs(ra) - length(q);
  float d2 = (q.y < 0.0) ? dot2(q + float2(ra, 0.0)) : u * u;
  float s = sign(a);
  return float4(sqrt(d2 + p.z * p.z) - w,
                (p.y > 0.0) ? s * u : s * sign(-p.x) * (q.x + ra),
                (p.y > 0.0) ? atan(s * p.y, -s * p.x) * ra
                            : (s * p.x < 0.0) ? p.y : l - p.y,
                p.z);
}
float sdfLink(float3 p, float le, float r1, float r2) {
  float3 q = float3(p.x, max(abs(p.y) - le, 0.0), p.z);
  return length(float2(length(q.xy) - r1, q.z)) - r2;
}
float sdfOctahedron(float3 p, float s) {
  p = abs(p);
  float m = p.x + p.y + p.z - s;
  float3 q;
  if (3.0 * p.x < m)
    q = p.xyz;
  else if (3.0 * p.y < m)
    q = p.yzx;
  else if (3.0 * p.z < m)
    q = p.zxy;
  else
    return m * 0.57735027;
  float k = clamp(0.5 * (q.z - q.y + s), 0.0, s);
  return length(float3(q.x, q.y - s + k, q.z - k));
}
float sfOctahedronBounded(float3 p, float s) {
  p = abs(p);
  return (p.x + p.y + p.z - s) * 0.57735027;
}
float sdfdPyramid(float3 p, float h) {
  float m2 = h * h + 0.25;
  p.xz = abs(p.xz);
  p.xz = (p.z > p.x) ? p.zx : p.xz;
  p.xz -= 0.5;
  float3 q = float3(p.z, h * p.y - 0.5 * p.x, h * p.x + 0.5 * p.y);
  float s = max(-q.x, 0.0);
  float t = clamp((q.y - 0.5 * p.z) / (m2 + 0.25), 0.0, 1.0);
  float a = m2 * (q.x + s) * (q.x + s) + q.y * q.y;
  float b =
      m2 * (q.x + 0.5 * t) * (q.x + 0.5 * t) + (q.y - m2 * t) * (q.y - m2 * t);
  float d2 = min(q.y, -q.x * m2 - q.y * 0.5) > 0.0 ? 0.0 : min(a, b);
  return sqrt((d2 + q.z * q.z) / m2) * sign(max(q.z, -p.y));
}
float udfTriangle(float3 p, float3 a, float3 b, float3 c) {
  float3 ba = b - a;
  float3 pa = p - a;
  float3 cb = c - b;
  float3 pb = p - b;
  float3 ac = a - c;
  float3 pc = p - c;
  float3 nor = cross(ba, ac);

  return sqrt(
      (sign(dot(cross(ba, nor), pa)) + sign(dot(cross(cb, nor), pb)) +
           sign(dot(cross(ac, nor), pc)) <
       2.0)
          ? min(min(dot2(ba * clamp(dot(ba, pa) / dot2(ba), 0.0, 1.0) - pa),
                    dot2(cb * clamp(dot(cb, pb) / dot2(cb), 0.0, 1.0) - pb)),
                dot2(ac * clamp(dot(ac, pc) / dot2(ac), 0.0, 1.0) - pc))
          : dot(nor, pa) * dot(nor, pa) / dot2(nor));
}
float udfQuad(float3 p, float3 a, float3 b, float3 c, float3 d) {
  float3 ba = b - a;
  float3 pa = p - a;
  float3 cb = c - b;
  float3 pb = p - b;
  float3 dc = d - c;
  float3 pc = p - c;
  float3 ad = a - d;
  float3 pd = p - d;
  float3 nor = cross(ba, ad);

  return sqrt(
      (sign(dot(cross(ba, nor), pa)) + sign(dot(cross(cb, nor), pb)) +
           sign(dot(cross(dc, nor), pc)) + sign(dot(cross(ad, nor), pd)) <
       3.0)
          ? min(min(min(dot2(ba * clamp(dot(ba, pa) / dot2(ba), 0.0, 1.0) - pa),
                        dot2(cb * clamp(dot(cb, pb) / dot2(cb), 0.0, 1.0) -
                             pb)),
                    dot2(dc * clamp(dot(dc, pc) / dot2(dc), 0.0, 1.0) - pc)),
                dot2(ad * clamp(dot(ad, pd) / dot2(ad), 0.0, 1.0) - pd))
          : dot(nor, pa) * dot(nor, pa) / dot2(nor));
}
