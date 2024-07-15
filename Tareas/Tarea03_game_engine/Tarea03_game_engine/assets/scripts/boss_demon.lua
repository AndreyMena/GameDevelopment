-- Variables globales
boss_speed = 0.5 * 64.0
lifes_boss = 5
cooldown = 0
cooldown_attack = 0
boss_idle_state = 1 
boss_attack_state = 2

boss_current_state = boss_idle_state
-- Funcion awake
function awake()
	set_velocity(this, -boss_speed, 0)
end

-- Funcion update
function update()
	-- body
	if boss_current_state == boss_idle_state then
		cooldown = cooldown +1;
	end
	print(cooldown)
	print(cooldown_attack)
	if boss_current_state == boss_attack_state then
		cooldown_attack = cooldown_attack + 1
 		if cooldown_attack == 500 then
			boss_current_state = boss_idle_state
			change_animation(this, "boss", "idle")
			cooldown_attack = 0
		end		
	end
	if cooldown == 500 then
		if boss_current_state ~= boss_attack_state then
			boss_current_state = boss_attack_state
			change_animation(this, "boss", "attack")
		end		
		cooldown = 0
	end
end


-- Funcion on_collision

function on_collision(other)
	if other:get_tag() == "floor" or other:get_tag() == "barrier" then
		local x_vel, y_vel = get_velocity(this)
		if check_dir_collision(this, other, "left") then
			flip_sprite(this, true)
			set_velocity(this, boss_speed, y_vel)
			if boss_current_state == boss_attack_state then
				set_velocity(this, boss_speed * 2, y_vel)
			end
		end
		if check_dir_collision(this, other, "right") then
			flip_sprite(this, false)
			set_velocity(this, -boss_speed, y_vel)
			if boss_current_state == boss_attack_state then
				set_velocity(this, -boss_speed * 2, y_vel)
			end
		end
	end	
	if other:get_tag() == "player" then
		
	end	
	if other:get_tag() == "arrow" then
		local x_vel, y_vel = get_velocity(this)
		if check_dir_collision(this, other, "left") then
			flip_sprite(this, false)
			set_velocity(this, -boss_speed, y_vel)
			if boss_current_state == boss_attack_state then
				set_velocity(this, -boss_speed * 2, y_vel)
			end
		end
		if check_dir_collision(this, other, "right") then
			flip_sprite(this, true)
			set_velocity(this, boss_speed, y_vel)
			if boss_current_state == boss_attack_state then
				set_velocity(this, boss_speed * 2, y_vel)
			end
		end
		lifes_boss = lifes_boss - 1

		--Para que vaya en direccion de donde se lanzo la flecha

		if lifes_boss == 0 then
			this:kill()
		end	
	end	
end
