math.randomseed(os.time())
Sphere(1):translate(15, 15, 20)
Box(1.0, 1.0, 1.0):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(10, 15, 20)
Torus(1.0, 0.5):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(5, 15, 20)
RoundBox(0.5, 0.5, 0.5, 0.5):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(0, 15, 20)
-- CappedTorus(0.866025,-0.5, 1.0, 0.5):rotate_x(math.pi/4):translate(0, 0, 10) (?,?,rBig,rSmall)
