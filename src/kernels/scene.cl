float3 p = (float3)(1.0, 2.0, 2.0);
sdf_elongate(sdf_sphere(1.0), float3(5.0, 0.0, 0.0))->dist(p);
