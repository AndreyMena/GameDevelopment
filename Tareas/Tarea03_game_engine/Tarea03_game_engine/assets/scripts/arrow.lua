

-- Funcion on_collision

function on_collision(other)
	if other:get_tag() == "floor" then
		print("arrowwwww")

		--local x_vel, y_vel = get_velocity(this)
		--if check_dir_collision(this, other, "left") then
		--	flip_sprite(this, true)
		--	set_velocity(this, enemy_speed, y_vel)
		--end
		--if check_dir_collision(this, other, "right") then
		--	flip_sprite(this, false)
		--	set_velocity(this, -enemy_speed, y_vel)
		--end
	end	
end
