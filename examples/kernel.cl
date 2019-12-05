void kernel gpu_render(global const uint2 img_bounds,
                       global const uint4 *tile_bounds, global float *color,
                       global float *albedo, global float *depth,
                       global float *normal, global const ulong randoms) {
    // RANDOM NUMBERS
    // ulong seed = randoms + globalID;
    // seed = (seed * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1);
    // uint
    const uint4 tile_bound = tile_bounds[get_global_id(0)];
    for (uint x = tile_bound.x; x < tile_bound.z; ++x) {
        for(uint y = tile_bound.y; y < tile_bound.w; ++y) {
            const uint idx = 3 * (y * img_bounds.y + x);
            color[idx + 0] = 1.0f;
            color[idx + 1] = 0.0f;
            color[idx + 2] = 1.0f;
        }
    }
}
