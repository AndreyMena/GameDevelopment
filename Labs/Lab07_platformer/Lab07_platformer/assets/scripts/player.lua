-- Variables globales

player_speed = 3.0 * 64.0 
player_jump_force = -1200.0 * 64.0 
player_can_jump = true 

-- Function update del jugador
function update()
	local x_vel, y_vel = get_velocity(this)
	x_vel = 0

	if get_action_state("jump") then
		-- print("jumping")
		if player_can_jump then
			player_can_jump = false
			add_force(this, 0, player_jump_force)
		end
	end

	if get_action_state("move_right") then
		print("right movement")
		x_vel = x_vel + player_speed
	end

	if get_action_state("move_left") then
		print("left movement")
		x_vel = x_vel - player_speed
	end

	set_velocity(this, x_vel, y_vel)
end
