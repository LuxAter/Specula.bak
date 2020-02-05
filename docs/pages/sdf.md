# Signed Distance Function(SDF)

> SOURCE: https://iquilezles.org/www/articles/distfunctions/distfunctions.htm

Here you will find the distance functions for some basic primitives and also
the operations needed to combine them together for building more complex
shapes. The list is not exhaustive, since many more primitives can be
generated through revolution or extrusion of [2D Distance Functions] as
explained in the second part of this page. I only added a few, but you can
easily construct your own.

I always favor using exact distance fields over distance bounds, so the
marchers are as accurate as possible and shadowing and lighting as uniform and
accurate as possible.

## Primitives

Mos of the following primitives are centered at the origin. You will have to
transform the point to get arbitrarily rotated and translated objects.

### Sphere - exact

```glsl
float sdSphere(vec3 p, float s) {
    return length(p) - s;
}
```

### Box - exact

```glsl
float sdBox(vec3 p, vec3 b) {
    vec3 q = abs(p) - b;
    return length(max(q, 0.0))) + min(max(q.x, max(q.y, q.z)), 0.0);
}
```

### Round Box - exact

```glsl
float sdRoundBox(vec3 p, vec3 b, float r) {
  vec3 q = abs(p) - b;
  return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0) - r;
}
```
