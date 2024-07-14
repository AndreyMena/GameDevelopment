-- Variables globales

player_idle_state = 1 
player_run_state = 2
player_jump_state = 3 
player_fall_state = 4 
player_attack_state = 5

player_current_state = player_idle_state

player_speed = 3.0 * 64.0 
player_jump_force = -2000.0 * 64.0 
player_can_jump = true

-- Funciones locales
function player_animation_state(attack)
	local x_vel, y_vel = get_velocity(this)

	if attack then
		player_current_state = player_attack_state
		change_animation(this, "player", "attack")
		return
	end

	if x_vel >= 0.01 then
		flip_sprite(this, false)
		if player_current_state ~= player_run_state then
			player_current_state = player_run_state
			change_animation(this, "player", "run")
		end
	end

	if x_vel <= -0.01 then
		flip_sprite(this, true)
		if player_current_state ~= player_run_state then
			player_current_state = player_run_state
			change_animation(this, "player", "run")
		end
	end

	if y_vel <= -0.01 then
		if player_current_state ~= player_jump_state then
			player_current_state = player_jump_state
			change_animation(this, "player", "jump")
		end
	end

	if y_vel >= 0.01 then
		if player_current_state ~= player_fall_state then
			player_current_state = player_fall_state
			change_animation(this, "player", "fall")
		end
	end

	if -0.01 < x_vel and x_vel < 0.01 and -0.01 < y_vel and y_vel < 0.01 then
		if player_current_state ~= player_idle_state then
			player_current_state = player_idle_state
			change_animation(this, "player", "idle")			
		end
	end
end

-- Function update del jugador
function update()
	local x_vel, y_vel = get_velocity(this)
	x_vel = 0
	attack = false;
	if get_action_state("jump") then
		-- print("jumping")
		if player_can_jump then
			player_can_jump = false
			add_force(this, 0, player_jump_force)
		end
	end

	if get_action_state("move_right") then
		--print("right movement")
		x_vel = x_vel + player_speed
	end

	if get_action_state("move_left") then
		--print("left movement")
		x_vel = x_vel - player_speed
	end

	if get_action_state("attack") then
		--print("attack movement")
		y_vel = 0;
		attack = true;
	end
	--print(x_vel..", "..y_vel)
	set_velocity(this, x_vel, y_vel)

	player_animation_state(attack)
end

-- Function onCollision

function on_collision(other)
	if other:get_tag() == "floor" then
		-- print(this:get_tag().." choca contra "..other:get_tag())
		if check_dir_collision(this, other, "bottom") then
			player_can_jump = true
		end
	end
	--print(this:get_tag().." choca contra "..other:get_tag())
	if other:get_tag() == "spikes" then		
	end
	if other:get_tag() == "enemy" or other:get_tag() == "boss" or other:get_tag() == "spikes" then		
		this:kill()
	end
	if other:get_tag() == "checkpoint" then
		win_level()
	end
end
