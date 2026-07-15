-- scripts/player.lua
local Player = {}

function Player.update(deltaTime)
   local movement = Vec2.zero;

  if Input.KeyDown(Keys.W) then
    movement.y = movement.y - 1.0;    
  end

  if Input.KeyDown(Keys.S) then
    movement.y = movement.y + 1.0;
  end

  if Input.KeyDown(Keys.A) then
    movement.x = movement.x - 1.0;
  end

  if Input.KeyDown(Keys.D) then
    movement.x = movement.x + 1.0;
  end

  movement = Vec2.scale(Vec2.normalize(movement), 200 * deltaTime);
  print("x: " .. movement.x .. ", y: " .. movement.y);
end

function Player.draw()
   -- code here
end

return Player
