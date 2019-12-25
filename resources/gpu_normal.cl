float3 normal_{0:020}(const float3 __point) {{
    const float3 p = mult3({1}, __point);
    return mult4({2},
        normalize((float4)(
                sdf_{0:020}((float3)(p.x + {3}, p.y, p.z)) -
                sdf_{0:020}((float3)(p.x - {3}, p.y, p.z)),
                sdf_{0:020}((float3)(p.x, p.y + {3}, p.z)) -
                sdf_{0:020}((float3)(p.x, p.y - {3}, p.z)),
                sdf_{0:020}((float3)(p.x, p.y, p.z + {3})) -
                sdf_{0:020}((float3)(p.x, p.y, p.z - {3})),
                0.0)));
}}
