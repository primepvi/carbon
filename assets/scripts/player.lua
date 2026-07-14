-- player.lua
local Player = {}

function Player.update(deltaTime)
   if Input.KeyPressed(Keys.W) then
      print("Apertou W")
   end

   if Input.KeyPressed(Keys.S) then
      print("Apertou S")
   end

   if Input.KeyPressed(Keys.A) then
      print("Apertou A")
   end
	 
   if Input.KeyPressed(Keys.D) then
      print("Apertou D")
   end
end

return Player
