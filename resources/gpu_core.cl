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

__kernel void render_tile(const global uint2 img_bounds, const global uint4* tile_bounds, global float3* color) {
    const o = mult3({0}, (float3)(0.0f, 0.0f, 0.0f));
    const uint4 tile_bound = tile_bounds[get_global_id(0)];
    for(uint x = tile_bound.x; x < tile_bound.z; ++x) {
        for(uint y = tile_bound.y; y < tile_bound.w; ++y) {
            const float3 dir = (float3)(x - img_bounds.x / 2.0f + frand(randoms), y - img_bounds.y / 2.0f + frand(randoms), {1));
        }
    }
}
