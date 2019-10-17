void kernel distance_estimator(global const float3 *origins,
                               global const float3 *dirs,
                               global float size, global int *obj_index,
                               global float *times, global float3 *normals) {
  int ID = get_global_id(0);
  int WORKERS = get_global_size(0);
  int step = (size / WORKERS);
  for (int i = ID; i < size; i += step) {
    int obj_ind = -1;
    float t = 0;
    while (t < 1e5f) {
      float3 p = origins[i] + dirs[i] * t;
      float dt = INFINITY;
      float odt = INFINITY;
      {{ for obj in objs }}
          odt = de_{{objs.id_}}(p);
          if (odt < dt) {
            dt = odt;
            if (odt < 1e-5f) {
              obj_ind = {{ obj.index }}
            }
          }
      {{ endfor }}
      if (dt < 1e-5f) {
        break;
      } else {
        t += dt;
      }
    }
    obj_index[i] = obj_ind;
    times[i] = t;
    if (obj_ind != -1) {
      normals[i] = (float3)(0.0f, 0.0f, 0.0f);
    } else {
      normals[i] = (float3)(0.0f, 0.0f, 0.0f);
    }
  }
}
