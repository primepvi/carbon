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

  local scene = Scene.GetCurrent()
  local cx = math.floor(transform.position.x / scene.camera.viewport.x) * scene.camera.viewport.x
  local cy = math.floor(transform.position.y / scene.camera.viewport.y) * scene.camera.viewport.y
  scene.camera.position = Vec2.new(cx, cy)
end

function Player:OnCollide(other)   
   if other.name == "Apple" then
      local appleSprite = other:FindComponent("Sprite")
      appleSprite.color = Color.FromRGB(math.random(), math.random(), math.random())

      local appleTransform = other:FindComponent("Transform")
      appleTransform.position = Vec2.new(math.random(0, 1000), math.random(0, 1000))

      local playerTransform = self.Node:FindComponent("Transform")
      playerTransform.scale = playerTransform.scale:scale(1.0)
   end
end

return Player
