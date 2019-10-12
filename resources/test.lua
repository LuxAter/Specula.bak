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
):translate(-5, 15, 20) -- (length, rBig, rSmall)
-- Cylinder(1.0):translate(0,0, 10) -- (radius)
Cone(math.pi / 4):translate(0, 0, 10) -- (angle)
