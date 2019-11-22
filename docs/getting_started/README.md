# Getting Started

The first step is to create a material for an object. To create a simple
diffuse material use this code snippet, to create a blue diffuse material.

```lua
mat = Material.new(0.0, 0.0, 1.0):set_type(Material.Type.DIFFUSE)
```

To create a light source, use this code snippet.

```lua
light_mat = Material.new(1.0, 1.0, 1.0):set_emission(1.0)
```

The next step is to define some objects to be rendered in the scene, we will
first define a box, and two spheres within the box.

```lua
Plane.new(1.0, 0.0, 0.0, -2.5):set_material(mat)
Plane.new(-1.0, 0.0, 0.0, 2.5):set_material(mat)
Plane.new(0.0, 1.0, 0.0, 0.0):set_material(mat)
Plane.new(0.0, -1.0, 0.0, 5.0):set_material(mat)
Plane.new(0.0, 0.0, 1.0, -2.0):set_material(mat)
Plane.new(0.0, 0.0, -1.0, 5.0):set_material(mat)

Sphere.new(2.0):translate(-0.5, 2.0, 3.0):set_material(light_mat)
Sphere.new(1.0):translate(1.5, 2.0, 1.0):set_material(light_mat)
```
