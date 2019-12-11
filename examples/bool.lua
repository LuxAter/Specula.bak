camera.set_pos(0.0, 0.0, -5.0)
camera.set_center(0.0, 0.0, 0.0)
camera.set_up(0.0, 1.0, 0.0)

light = Material.Emissive(1.0, 1.0, 1.0, 1.0)
white = Material.Diffuse(1.0, 1.0, 1.0)
red = Material.Emissive(1.0, 1.0, 0.0, 0.0)
green = Material.Emissive(1.0, 0.0, 1.0, 0.0)
blue = Material.Emissive(1.0, 0.0, 0.0, 1.0)
yellow = Material.Emissive(1.0, 1.0, 1.0, 0.0)
cyan = Material.Emissive(1.0, 0.0, 1.0, 1.0)
magenta = Material.Emissive(1.0, 1.0, 0.0, 1.0)

sph = Sphere.new(2.0)
box = Box.new(1.5, 1.5, 1.5)
inter = Intersection(sph, box)
xa = Cylinder.new(0.1, 2.0):rotate(math.pi / 2, 0.0, 0.0, 1.0)
ya = Cylinder.new(0.1, 2.0)
za = Cylinder.new(0.1, 2.0):rotate(math.pi / 2, 1.0, 0.0, 0.0)
cross = Union(Union(xa, ya), za)
final = Subtract(cross, inter)
final:set_material(white)

Sphere.new(50):translate(0.0, 70, 0.0):set_material(light)

xp = Sphere.new(0.3):set_material(red)
xn = Sphere.new(0.3):set_material(cyan)
yp = Sphere.new(0.3):set_material(green)
yn = Sphere.new(0.3):set_material(magenta)
zp = Sphere.new(0.3):set_material(blue)
zn = Sphere.new(0.3):set_material(yellow)

for t = 0, 1, 10 / 720 do
  theta = t * 4 * math.pi
  phi = t * 2 * math.pi
  r = -math.cos(2*phi)
  xa.radius = r
  ya.radius = r
  za.radius = r
  camera.set_pos(6 * math.sin(theta), math.sin(3 * theta), 6 * math.cos(theta))

  xp:translate(math.cos(phi) + 1.3, 0.0, 0.0)
  xn:translate(-math.cos(phi) - 1.3, 0.0, 0.0)
  yp:translate(0.0, math.cos(phi) + 1.3, 0.0)
  yn:translate(0.0, -math.cos(phi) - 1.3, 0.0)
  zp:translate(0.0, 0.0, math.cos(phi) + 1.3)
  zn:translate(0.0, 0.0, -math.cos(phi) - 1.3)
  render()

  xp:translate(-math.cos(phi) - 1.3, 0.0, 0.0)
  xn:translate(math.cos(phi) + 1.3, 0.0, 0.0)
  yp:translate(0.0, -math.cos(phi) - 1.3, 0.0)
  yn:translate(0.0, math.cos(phi) + 1.3, 0.0)
  zp:translate(0.0, 0.0, -math.cos(phi) - 1.3)
  zn:translate(0.0, 0.0, math.cos(phi) + 1.3)
end
