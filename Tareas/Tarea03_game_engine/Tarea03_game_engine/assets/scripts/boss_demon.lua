-- Variables globales
enemy_speed = 0.5 * 64.0
lifes = 5

-- Funcion awake
function awake()
	set_velocity(this, -enemy_speed, 0)
end

-- Funcion update
function update()
	-- body
end


-- Funcion on_collision

function on_collision(other)
	if other:get_tag() == "floor" then
		local x_vel, y_vel = get_velocity(this)
		if check_dir_collision(this, other, "left") then
			flip_sprite(this, true)
			set_velocity(this, enemy_speed, y_vel)
		end
		if check_dir_collision(this, other, "right") then
			flip_sprite(this, false)
			set_velocity(this, -enemy_speed, y_vel)
		end
	end	
	if other:get_tag() == "player" then
		
	end	
	if other:get_tag() == "arrow" then
		lifes = lifes - 1

		--Para que vaya en direccion de donde se lanzo la flecha

		if lifes == 0 then
			this:kill()
		end	
	end	
end