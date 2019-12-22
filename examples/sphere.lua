camera.set_pos(2.78, 2.73, -8.0)
camera.set_direction(0.0, 0.0, 1.0)
camera.set_up(0.0, 1.0, 0.0)

light = Material.Emissive(1.0, 1.0, 1.0, 1.0)
white = Material.Diffuse(1.0, 1.0, 1.0)
red = Material.Diffuse(1.0, 0.0, 0.0)
green = Material.Diffuse(0.0, 1.0, 0.0)
blue = Material.Diffuse(0.0, 0.0, 1.0)
glass = Material.Transparent(1.5)

Plane.new(0.0, 1.0, 0.0, 0.0):set_material(white)
Plane.new(0.0, -1.0, 0.0, 5.5):set_material(light)
Plane.new(0.0, 0.0, 1.0, 8.1):set_material(white)
Plane.new(0.0, 0.0, -1.0, 5.592):set_material(green)
Plane.new(1.0, 0.0, 0.0, 0.0):set_material(blue)
Plane.new(-1.0, 0.0, 0.0, 5.528):set_material(red)
Sphere.new(2.0):translate(3.528, 2.0, 3.592):set_material(white)
Torus.new(1.0, 0.3):set_material(glass):rotate(-math.pi / 4, 1.0, 0.0, 0.0):translate(
  1.3,
  1.0,
  1.5
)
