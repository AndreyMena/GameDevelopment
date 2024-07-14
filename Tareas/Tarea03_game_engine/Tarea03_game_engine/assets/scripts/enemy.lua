-- Variables globales
enemy_speed = 0.5 * 100.0
lifesEnemy = 3

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
	if other:get_tag() == "floor" or other:get_tag() == "enemy" or other:get_tag() == "player" then
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
	if other:get_tag() == "arrow" then
		local x_vel, y_vel = get_velocity(this)
		if check_dir_collision(this, other, "left") then
			flip_sprite(this, false)
			set_velocity(this, -enemy_speed, y_vel)
		end
		if check_dir_collision(this, other, "right") then
			flip_sprite(this, true)
			set_velocity(this, enemy_speed, y_vel)
		end
		lifesEnemy = lifesEnemy - 1
		print(lifesEnemy);
		--Para que vaya en direccion de donde se lanzo la flecha

		if lifesEnemy == 0 then

			this:kill()
		end	
	end	
end
