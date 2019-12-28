float3 mult3(const float16 mat, const float3 p) {
    return (float3)(
            p.x * mat.s0 + p.y * mat.s1 + p.z * mat.s2 + mat.s3,
            p.x * mat.s4 + p.y * mat.s5 + p.z * mat.s6 + mat.s7,
            p.x * mat.s8 + p.y * mat.s9 + p.z * mat.s10 + mat.s11)
}
float4 mult4(const float16 mat, const float4 p) {
    return (float3)(
            p.x * mat.s0 + p.y * mat.s1 + p.z * mat.s2 + p.w * mat.s3,
            p.x * mat.s4 + p.y * mat.s5 + p.z * mat.s6 + p.w * mat.s7,
            p.x * mat.s8 + p.y * mat.s9 + p.z * mat.s10 + p.w * mat.s11,
            p.x * mat.s12 + p.y * mat.s13 + p.z * mat.s14 + p.w * mat.s15)
}

float3 ray_trace(const local float3 o, const local float3 d, const local ulong medium, const local uint depth, global uint* randoms) {
    if(depth >= {1}) { // MIN BOUNCE
        if(frand(randoms) < 0.01f) {
            return (float3)(0.0f, 0.0f, 0.0f);
        }
    }
    float t = INFINITY;
    ulong obj = 0;
    ray_march(o, d, &t, &obj);
    if(obj == 0){
        return (float3)(0.0f, 0.0f, 0.0f);
    }
    const ulong material = get_material(obj)
    const float3 p = o + t * d;
    const float3 normal = get_normal(obj, p);
    const float3 dir = sample_bsdf(medium, material, d, normal);
    float3 ri = {2} // SKY COLOR
    if(dir != (float3)(0.0f)) {
        if(get_material_type(material) == 2) {
            if(get_material_type(medium) == 2) {
                const float3 refact_dir = sample_bsdf(medium, material, d, -normal);
            }
        }
    }
}

__kernel void render_tile(const global uint4 img_bounds, const global uint4* tile_bounds, global uint spp, global float3* color, global uint* randoms) {
    const o = mult3({0}, (float3)(0.0f, 0.0f, 0.0f)); // VIEW
    const uint4 tile_bound = tile_bounds[get_global_id(0)];
    for(uint x = tile_bound.x; x < tile_bound.z; ++x) {
        for(uint y = tile_bound.y; y < tile_bound.w; ++y) {
            const float3 dir = (float3)(x - img_bounds.x / 2.0f + frand(randoms), y - img_bounds.y / 2.0f + frand(randoms), {1));
            color[(img_bounds.y - (1 + y)) * img_bounds.w + x] += (ray_trace(o, normalize(mult4({0}, (float4)(dir, 0.0f))), 0, 0, randoms) / spp);
        }
    }
}
