# API Reference

## Camera

The camera is already provided to any lua script as the variable ``camera``. To
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
*Principled BSDF* developed by Disney.

### Enumerations

#### Type

``Material.Type.DIFFUSE``
: Creates a perfictly diffuse material

``Material.Type.SPECULAR``
: Creates a perfictly reflective material.

``Material.Type.REFRACTIVE``
: Creates a perfictly refractive material.

### Member Variables

#### color

This is the base color of the material in a RGB format.

#### type

This defines the type of the material from one of the available options.
