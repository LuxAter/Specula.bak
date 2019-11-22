# API Reference

## Camera

The camera is already provided to any lua script as the variable `camera`. To
control the camera, there are three methods provided.

### Methods

#### eye

```lua
camera:eye(x, y, z)
```

This method sets the position of the camera/eye in the world space. It requires
three parameters, $x$, $y$, and $z$ position in world space to move the camera
to. This defaults to $(0.0, 0.0, -1.0)$.

#### center

```lua
camera:center(x, y, z)
```

This method sets the position that the camera will focus on in the world space.
It requires three parameters, $x$, $y$, and $z$ position of the focuse location
in world space. This defaults to $(0.0, 0.0, 0.0)$.

#### up

```lua
camera:up(x, y, z)
```

This method sets the direction that the camera considers "up". This direction
will be used to define what will be at the top of the rendered image, and what
will be at the bottom. This defaults to $(0.0, 1.0, 0.0)$.

## Material

The Material is a type that is provided to lua scripts, that allows for the
creation and alterations of materials.

!> More work must be done on the material and shader models, to implement the
_Principled BSDF_ developed by Disney.

### Enumerations

#### Type

`Material.Type.DIFFUSE`
: Creates a perfictly diffuse material

`Material.Type.SPECULAR`
: Creates a perfictly reflective material.

`Material.Type.REFRACTIVE`
: Creates a perfictly refractive material.

### Member Variables

#### color

This is the base color of the material in a RGB format. Each component must be
in range of $[0,1]$.

#### type

This defines the type of the material from one of the available options on the
[`Type`](#Type) enumeration.

#### emission

This defines the strength of the emission of the object, this must be in the
range $[0,1]$. This defaults to $0.0$, meaning no light is emitted.

#### ior

This defines the index of refraction for the material. This defaults to $1.0$.

### Methods

#### set_color

```lua
mat:set_color(r, g, b)
```

This method sets the color variable of the material to the associated values
for $r$, $g$, and $b$, where each element is within the range $[0,1]$.

#### set_type

```lua
mat:set_type(type)
```

This method sets the type of shading to utilize for the shading of the
material, the value of `type` must be an element of [`Type`](#type).

#### set_emission

```lua
mat:set_emission(emission)
```

This method sets the emission variable of the material to the provided value,
which must be within the range $[0,1]$.

#### set_ior

```lua
mat:set_ior(ior)
```

This method sets the ior variable of the material to the provided value.

## Object

These methods apply to any derived object, which can be found in this list.

Each object defines the basic setting function for the different variables of
an object. For example, the ``Sphere`` type has ``set_radius(radius)``.

- `Sphere.new(radius)`
- `Box.new(width, height, length)`
- `Cone.new(height, radius_base, radius_top)`
- `Cylinder.new(height, radius)`
- `Plane.new(x, y, z, offset)`
- `Torus.new(radius, radius_of_revolution)`
- `Quad.new(ax, ay, az, bx, by, bz, cx, cy, cz, dx, dy, dz)`

### Methods

#### translate

```lua
obj:translate(x,y,z)
```

Translates the location of the object to by the given values for $x$, $y$, and
$z$.

#### rotate_x

```lua
obj:rotate_x(angle)
```

Rotates the object about the $x$ axis by the given angle in radians.

#### rotate_y

```lua
obj:rotate_y(angle)
```

Rotates the object about the $y$ axis by the given angle in radians.

#### rotate_z

```lua
obj:rotate_z(angle)
```

Rotates the object about the $z$ axis by the given angle in radians.

#### scale

```lua
obj:scale(x, y, z)
```

Scales object in each axis respectivly.

#### set_material

```lua
obj:set_material(mat)
```

This sets the material of the object to a given [material](#material) object.
