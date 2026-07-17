-- scripts/player.lua
local Player = {}

function Player:Update(deltaTime)
  local movement = Vec2.new(0, 0)
   
  if Input.KeyDown(Keys.W) then
    movement.y = movement.y + 1.0
  end

  if Input.KeyDown(Keys.S) then
    movement.y = movement.y - 1.0
  end

  if Input.KeyDown(Keys.A) then
    movement.x = movement.x - 1.0
  end

  if Input.KeyDown(Keys.D) then
    movement.x = movement.x + 1.0
  end

  movement = Vec2.scale(movement:normalize(), 200 * deltaTime)

  local transform = self.Node:FindComponent("Transform")
  transform.position = transform.position + movement
end

function Player:OnCollide(other)
   print(other.name)
end

return Player
