math.randomseed(os.time())
Sphere(1):translate(15, 15, 20) -- (radius)
Box(1.0, 1.0, 1.0):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(10, 15, 20) -- (width x, length z, height y)
Torus(1.0, 0.5):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(5, 15, 20) -- (rBig, rSmall)
RoundBox(0.5, 0.5, 0.5, 0.5):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(0, 15, 20) -- (width x, length z, height y, radius)
-- CappedTorus(0.866025,-0.5, 1.0, 0.5):rotate_x(math.pi/4):translate(0, 0, 10) (?,?,rBig,rSmall)
Link(1.0, 1.0, 0.5):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(-10, 15, 20) -- (length, rBig, rSmall)
-- InfiniteCylinder(1.0):translate(0,0, 10) -- (radius) -- INFINITE
-- Cone(math.pi / 4):rotate_x(math.pi/2):translate(0, 0, 10) -- (angle) -- INFINITE
-- Plane(1,1,1,0):rotate_x(math.pi/2):translate(0,-50,0) -- (??,??,??,??) -- INFINITE
HexagonalPrism(1.0, 1.0):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(5, 10, 20) -- (radius, length)
TriangularPrism(1.0, 1.0):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(0, 10, 20) -- (radius, length)
Capsule(0, 0, 0, 1, 1, 0, 0.2):translate(-5, 10, 20) -- (x1,y1,z1,x2,y2,z2,r)
VerticalCapsule(1.0, 0.5):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(-10, 10, 20) -- (height, radius)
CappedCylinder(1.0, 0.5):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(-15, 10, 20) -- (height, radius)
RoundedCylinder(0.5, 0.5, 1.0):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(15, 5, 20) -- (radius, round_radius, height)
CappedCone(1.0, 0.5, 1.0):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(10, 5, 20) -- (height, top_radius, bottom_radius)
SolidAngle(4 / 5, 4 / 5, 1.0):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(0, 0, 10)
