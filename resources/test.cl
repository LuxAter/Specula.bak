float2 q(length(p.xz), p.y);
float2 k1(r2, height);
float2 k2(r2 - r1, 2.0f * height);
float2 ca(q.x - min(q.x, (q.y < 0.0f) ? r1 : r2), fabs(q.y) - h);
float2 cb = q - k1 + k2 * clamp(dot(k1 - q, k2) / dot(k2, k2), 0.0f, 1.0f);
float s = (cb.x < 0.0f && ca.y < 0.0f) ? -1.0f : 1.0f;
return s * sqrt(min(dot(ca, ca), dot(cb, cb)));
