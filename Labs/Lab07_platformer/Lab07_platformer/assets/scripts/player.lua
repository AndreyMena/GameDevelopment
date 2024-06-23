-- Function update del jugador

player_jump_force = -1200.0 * 64.0 
player_can_jump = true 

function update()
	if get_action_state("jump") then
		print("jumping")
		if player_can_jump then
			player_can_jump = false
			add_force(this, 0, player_jump_force)
		end
	end

	if get_action_state("move_right") then
		print("right movement")
	end

	if get_action_state("move_left") then
		print("left movement")
	end
end
