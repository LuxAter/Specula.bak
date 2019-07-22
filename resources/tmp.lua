local inspect = require('inspect')

function test(args)
  print(inspect(args));
end

test{pos={0.0, -1.0, 1.0}, radius=1.0, color="#ff00ff"}
