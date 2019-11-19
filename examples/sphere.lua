-- TODO: WHY IS IT ABOVE US??? I.E. setting camera eye to +5 moves us down <08-11-19, Arden Rasmussen> --
l = Material.new(1.0, 1.0, 1.0)
l.emission = 1.0
r = Material.new(1.0, 0.0, 0.0):set_type(Material.Type.DIFFUSE)
g = Material.new(0.0, 1.0, 0.0):set_type(Material.Type.DIFFUSE)
b = Material.new(0.0, 0.0, 1.0):set_type(Material.Type.DIFFUSE)

d = Material.new(1.0, 1.0, 1.0):set_type(Material.Type.DIFFUSE)
s = Material.new(1.0, 1.0, 1.0):set_type(Material.Type.SPECULAR)
Sphere.new(5.0):translate(0.0, 0.0, 0.0):set_material(d)
Plane.new(0.0, -1.0, 0.0, 1.0):rotate_z(math.pi):translate(0.0, -10.0, 0.0):set_material(l)
Plane.new(0.0, -1.0, 0.0, 1.0):rotate_z(-math.pi/2):translate(10.0, 0.0, 0.0):set_material(r)
Plane.new(0.0, -1.0, 0.0, 1.0):rotate_z(math.pi/2):translate(-10.0, 0.0, 0.0):set_material(g)
Plane.new(0.0, -1.0, 0.0, 1.0):rotate_z(0.0):translate(0.0, 10.0, 0.0):set_material(d)
Plane.new(0.0, -1.0, 0.0, 1.0):rotate_x(-math.pi/2):translate(0.0, 0.0, -10.0):set_material(b)
Plane.new(0.0, -1.0, 0.0, 1.0):rotate_x(math.pi/2):translate(0.0, 0.0, 10.0):set_material(d)
camera:center(0.0, 0.0, 0.0)
for t = 0, 2 * math.pi, math.pi / 10 do
  camera:eye(8 * math.sin(t), 0.0, 8 * math.cos(t))
  render()
end
