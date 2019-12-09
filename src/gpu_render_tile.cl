uint rand(global uint *randoms) {
    randoms[get_global_id(0)] =
        (0x41C64E6D * randoms[get_global_id(0)] + 0x3039) % 0x80000000;
    return randoms[get_global_id(0)];
}
float frand(global uint *randoms) {
    randoms[get_global_id(0)] =
        (0x41C64E6D * randoms[get_global_id(0)] + 0x3039) % 0x80000000;
    return (float)randoms[get_global_id(0)] / (float)0x80000000;
}
float gpu_ray_march(const local float3 o, const local float3 d, int* obj) {
    float t = 0.0f;
    *obj = -1;
    bool first = true;
    while (t < {{t_max}}) {
        float3 p = p + d * t;
        float dt = INFINITY;
        float obj_dt = INFINITY;
        {{ for i in obj }}
        obj_dt = distance_{{i}}(p);
        if(obj_dt < dt) {
            dt = obj_dt;
            if(obj_dt < {{ epsilon }}) {
                obj = {{i}};
            }
        }
        {{ endfor }}
        if(!first && dt < {{ epsilon }}) {
            break;
        }else {
            t += dt;
        }
        first = false;
    }
    return t;
}
void gpu_ray_trace(const local float3 o, const local float3 d, local float3 *c,
        local float3 *a, local float3 *d, local float3 *n,
        local ulong depth, global uint *randoms) {
    if(depth >= {{min_bounce}}) {
        const local float rr_stop_prob = 0.01f;
        if(frand() < rr_stop_prob) {
            c = (float3)(0.0f);
            a = (float3)(0.0f);
            d = (float3)(0.0f);
            n = (float3)(0.0f);
            return;
        }
    }
    int id;
    float t = gpu_ray_march(o, d, &obj);
    float3 p = o + d * t;
    if(obj == -1) {
        c = {{sky}};
        a = {{sky}};
        d = (float3)(t);
        n = (float3)(0.0f);
        return;
    }
    {{ for i in obj }}
    else if(obj == {{i}}) {
        *n = normal_{{i}}(p, {{ epsilon }});
        *c = material_{{i}} 
    }
    {{ endfor }}
    float3 p = o + d * t;
    return;
}
void kernel gpu_render_tile(const uint2 img_bounds,
        global const uint4 *tile_bounds,
        global float *color, global float *albedo,
        global float *depth, global float *normal,
        global uint *randoms) {
    float3 o = (float3)(0.0f, 0.0f, 0.0f);
    o = {{view}} * (float4)(o, 1.0f);
    const uint4 tile_bound = tile_bounds[get_global_id(0)];
    for (uint x = tile_bound.x; x < tile_bound.z; ++x) {
        for (uint y = tile_bound.y; y < tile_bound.w; ++y) {
            float3 dir =
                (float3)(x - imb_bounds.x / 2.0f + frand(randoms),
                        y - img_bounds.y / 2.0f + frand(randoms), {{filmz}});
            float3 c, a, d, n;
            gpu_ray_trace(0, normalize((float3)(view * (float4)(dir, 0.0f))), &c, &a,
                    &d, &n, 0, randoms);
            const uint idx = 3 * (y * img_bounds.y + x);
            color[idx + 0] = c.x;
            color[idx + 1] = c.y;
            color[idx + 2] = c.z;
            albedo[idx + 0] = a.x;
            albedo[idx + 1] = a.y;
            albedo[idx + 2] = a.z;
            depth[idx + 0] = d.x;
            depth[idx + 1] = d.y;
            depth[idx + 2] = d.z;
            normal[idx + 0] = n.x;
            normal[idx + 1] = n.y;
            normal[idx + 2] = n.z;
        }
    }
}
