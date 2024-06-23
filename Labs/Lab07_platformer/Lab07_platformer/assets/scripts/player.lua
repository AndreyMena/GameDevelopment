-- Function update del jugador

function update()
	if get_action_state("jump") then
		print("jumping")
	end

	if get_action_state("move_right") then
		print("right movement")
	end

	if get_action_state("move_left") then
		print("left movement")
	end
end
