lights = {}
engine = RAY_MARCH -- RAY_TRACE RAY_MARCH PATH_TRACE PATH_MARCH
frames = 360

function setup()
  opaque = material.new{color="#ffffff", reflectivity=0.0, opacity=1.0}
  object.Plane{pos={0.0, -1.0, 0.0}, norm={0.0, 1.0, 0.0}, mat=opaque}
  object.Plane{pos={0.0, 0.0, 1.0}, norm={0.0, 0.0, -1.0}, mat=opaque}
  object.Sphere{pos={0.0, 0.0, 0.0}, radius=1.0, mat=opaque}
  lights[0] = light.Point{pos={0.0, 1.0, 0.0}, color="#ff0000"}
  lights[1] = light.Point{pos={0.0, 1.0, 0.0}, color="#00ff00"}
  lights[2] = light.Point{pos={0.0, 1.0, 0.0}, color="#0000ff"}
end

function frame(i)
  lights[0]:pos(math.sin(2*i), nil, nil)
  lights[1]:pos(math.sin(3*i), nil, nil)
  lights[2]:pos(math.sin(4*i), nil, nil)
end
