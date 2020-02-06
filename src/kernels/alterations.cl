class SdfElongate : public Sdf {
public:
  SdfElongate(const Sdf* primitive, float3 h) : primitive(primitive), h(h) {}
  virtual inline float dist(float3 p) override const {
    float3 q = abs(p) - h;
    return primitive->dist(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0);
  }

private:
  const Sdf* primitive;
  float3 h;
};
class SdfRound : public Sdf {
public:
  SdfRound(const Sdf* primitive, float r) : primitive(primitive), r(r) {}
  virtual inline float dist(float3 p) override const {
    return primitive(p) - r;
  }

private:
  const Sdf* primitive;
  float r;
};
