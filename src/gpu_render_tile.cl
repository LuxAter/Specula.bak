uint rand(global uint *randoms) {
    randoms[get_global_id(0)] = (0x41C64E6D*randoms[get_global_id(0)] + 0x3039) % 0x80000000;
    return randoms[get_global_id(0)];
}
float frand(global uint *randoms) {
    randoms[get_global_id(0)] = (0x41C64E6D*randoms[get_global_id(0)] + 0x3039) % 0x80000000;
    return (float)randoms[get_global_id(0)] / (float)0x80000000;
}
void kernel gpu_render_tile(const uint2 img_bounds,
        global const uint4 *tile_bounds, global float *color,
        global float *albedo, global float *depth,
        global float *normal, global uint *randoms) {
    // RANDOM NUMBERS
    const float r = frand(randoms);
    const float g = frand(randoms);
    const float b = frand(randoms);
    const uint4 tile_bound = tile_bounds[get_global_id(0)];
    // printf("(%u,%u,%u,%u)->(%f,%f,%f)\n", tile_bound.x, tile_bound.y, tile_bound.z, tile_bound.w, r, g, b);
    for (uint x = tile_bound.x; x < tile_bound.z; ++x) {
        for(uint y = tile_bound.y; y < tile_bound.w; ++y) {
            const uint idx = 3 * (y * img_bounds.y + x);
            color[idx + 0] = r;
            color[idx + 1] = g;
            color[idx + 2] = b;
        }
    }
}
