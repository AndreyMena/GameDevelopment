

-- Funcion on_collision

function on_collision(other)

	--print(this:get_tag().." chocaa contra "..other:get_tag())
end

-- Function update del jugador
function update()
	local x_vel, y_vel = get_velocity(this)

	set_velocity(this, x_vel, 0)
	--print("update arrow")
end