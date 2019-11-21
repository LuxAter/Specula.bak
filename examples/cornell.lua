camera:eye(2.78, 2.73, -8.00)
camera:direction(0.0, 0.0, 1.0)
camera:up(0.0, 1.0, 0.0)

light_mat = Material.new(1.0, 1.0, 1.0):set_emission(1.0)

white_mat = Material.new(1.0, 1.0, 1.0):set_type(Material.Type.DIFFUSE)
green_mat = Material.new(0.0, 1.0, 0.0):set_type(Material.Type.DIFFUSE)
red_mat = Material.new(1.0, 0.0, 0.0):set_type(Material.Type.DIFFUSE)

floor = Plane.new(0.0, 1.0, 0.0, 0.0):set_material(white_mat)
ceiling = Plane.new(0.0, -1.0, 0.0, 5.5):set_material(light_mat)
back_wall = Plane.new(0.0, 0.0, -1.0, 5.592):set_material(white_mat)
right_wall = Plane.new(1.0, 0.0, 0.0, 0.0):set_material(green_mat)
left_wall = Plane.new(-1.0, 0.0, 0.0, 5.528):set_material(red_mat)
front_wall = Plane.new(0.0, 0.0, 1.0, -8.1):set_material(white_mat)
