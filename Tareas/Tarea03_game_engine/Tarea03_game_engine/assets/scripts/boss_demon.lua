-- Variables globales
boss_speed = 0.5 * 64.0
lifes_boss = 5

-- Funcion awake
function awake()
	set_velocity(this, -boss_speed, 0)
end

-- Funcion update
function update()
	-- body
end


-- Funcion on_collision

function on_collision(other)
	if other:get_tag() == "floor" or other:get_tag() == "barrier" then
		local x_vel, y_vel = get_velocity(this)
		if check_dir_collision(this, other, "left") then
			flip_sprite(this, true)
			set_velocity(this, boss_speed, y_vel)
		end
		if check_dir_collision(this, other, "right") then
			flip_sprite(this, false)
			set_velocity(this, -boss_speed, y_vel)
		end
	end	
	if other:get_tag() == "player" then
		
	end	
	if other:get_tag() == "arrow" then
		local x_vel, y_vel = get_velocity(this)
		if check_dir_collision(this, other, "left") then
			flip_sprite(this, false)
			set_velocity(this, -boss_speed, y_vel)
		end
		if check_dir_collision(this, other, "right") then
			flip_sprite(this, true)
			set_velocity(this, boss_speed, y_vel)
		end
		lifes_boss = lifes_boss - 1

		--Para que vaya en direccion de donde se lanzo la flecha

		if lifes_boss == 0 then
			this:kill()
		end	
	end	
end
