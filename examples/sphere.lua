-- TODO: WHY IS IT ABOVE US??? I.E. setting camera eye to +5 moves us down <08-11-19, Arden Rasmussen> --
Sphere.new(1.0)
-- Box.new(1.0, 2.0, 3.0)
camera:center(0.0, 5.0, 0.0)
-- camera:up(0.0, -1.0, 0.0)
for t = 0, 2 * math.pi, math.pi / 10 do
  camera:eye(5 * math.sin(t), 5.0, 5 * math.cos(t))
  render()
end
