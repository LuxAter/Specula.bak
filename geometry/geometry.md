# Geometry #

The geometry system that is used in Specula allows for complex construction of
gemoetric object from combinations of primatives. It also allows for the
loading of triangular meshes, and defining custom geometric primatives.

## Primatives ##

### Sphere ###

```lua
Sphere(radius)
```

#### Parameters ####

* ``radius`` is the radius of the sphere.

### Box ###

```lua
Box(width, length, height)
```

#### Parameters ####

* ``width`` is the width of the box in the $x$ axis.
* ``length`` is the length of the box in the $y$ axis.
* ``height`` is the height of the box in the $x$ axis.

### Round Box ###

```lua
RoundBox(width, length, height, radius)
```

#### Parameters ####

* ``width`` is the width of the box in the $x$ axis.
* ``length`` is the length of the box in the $y$ axis.
* ``height`` is the height of the box in the $x$ axis.
* ``radius`` is the radius of the curve along the edges and corners.

#### Note ####

The ``radius`` is added to each axis of the box, so it will be larger than any
of the values entered.

### Torus ###

```lua
Torus(rBig, rSmall)
```

#### Parameters ####

* ``rBig`` is the radius of the overall ring of revolution.
* ``rSmall`` is the radius of the circle that it revolved around that ring.

### Capped Torus ###

```lua
Torus(rBig, rSmall, ra, rb)
```

#### Parameters ####

* ``rBig`` is the radius of the overall ring of revolution.
* ``rSmall`` is the radius of the circle that it revolved around that ring.
* ``ra`` UNKNOWN
* ``rb`` UNKNOWN
