-- TODO: WHY IS IT ABOVE US??? I.E. setting camera eye to +5 moves us down <08-11-19, Arden Rasmussen> --
l = Material.new(1.0, 1.0, 1.0)
l.emission = 1.0
r = Material.new(1.0, 0.0, 0.0)
r.emission = 1.0
g = Material.new(0.0, 1.0, 0.0)
g.emission = 1.0
b = Material.new(0.0, 0.0, 1.0)
b.emission = 1.0
-- Sphere.new(6.0):set_material(l):translate(0.0, 10.0, 0.0)

m = Material.new(1.0, 1.0, 1.0)
-- m:set_type(Material.Type.SPECULAR)
-- Sphere.new(1.0):set_material(l):translate(0.0, 0.0, 0.0)
-- Sphere.new(1.0):set_material(r):translate(4.0, 0.0, 0.0)
-- Sphere.new(1.0):set_material(g):translate(0.0, 4.0, 0.0)
-- Sphere.new(1.0):set_material(b):translate(0.0, 0.0, 4.0)
Box.new(1.0, 1.0, 1.0):set_material(m)
-- Plane.new(0.0, 1.0, 0.0, 0.0):rotate_z(math.pi):translate(0.0, 0.0, 0.0):set_material(l)
-- Cylinder.new(5.0, 0.5)
-- Cone.new(2.0, 0.5, 0.0):rotate_x(math.pi/5)
-- Torus.new(1.0, 0.3):rotate_x(math.pi/2):set_material(white_diff)
camera:center(0.0, 0.0, 0.0)
for t = 0, 2 * math.pi, math.pi / 10 do
  camera:eye(8 * math.sin(t), 0.0, 8 * math.cos(t))
  -- render()
end
