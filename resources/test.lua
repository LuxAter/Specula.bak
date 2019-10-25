math.randomseed(os.time())

light = Material({color = {1.0, 1.0, 1.0}, emission = 1.0})
blue = Material({color = {1.0, 0.0, 1.0}, emission=1.0})

Sphere(0.5):material(light):translate(0, -5, 5)
Torus(2.0, 1.0):material(blue):rotate(
  2.0 * math.random() * math.pi,
  math.random(),
  math.random(),
  math.random()
):translate(0, 0, 5)
