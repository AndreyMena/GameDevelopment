#pragma once

#include "../Bindings/LuaBindings.h"
#include "../ECS/ECS.h"
#include "../Components/ScriptComponent.h"

#include <iostream>
#include <memory>
#include <sol/sol.hpp>

class ScriptSystem : public System {
public:
	ScriptSystem() {
		RequireComponent<ScriptComponent>();
	}
	
	void CreateLuaBindings(sol::state& lua) {
		lua.new_usertype<Entity>(
			"entity",
			"get_tag", &Entity::GetTag,
			"kill", &Entity::Kill
		);

		lua.set_function("get_action_state",  GetActionState);

		lua.set_function("add_force", AddForce);
		lua.set_function("set_velocity", SetVelocity);
		lua.set_function("get_velocity", GetVelocity);
		lua.set_function("get_lifes", GetLifes);
		lua.set_function("discount_life", DiscountLife);
		lua.set_function("reload_level", ReloadLevel);

		lua.set_function("flip_sprite", FlipSprite);

		lua.set_function("change_animation", ChangeAnimation);

		lua.set_function("check_dir_collision", CheckDirectionCollision);

		lua.set_function("block_action", BlockActionStates);
		lua.set_function("allow_action", AllowActionStates);

		lua.set_function("win_level", WinLevel);
	}

	void Awake(sol::state& lua, std::shared_ptr<ECSManager> manager) {
		for (auto entity : manager->GetEntitiesToBeAdded()) {
			if (entity.HasComponent<ScriptComponent>()) {
				const auto& script = entity.GetComponent<ScriptComponent>();
				lua["this"] = entity;
				if (script.awake != sol::nil) {
					script.awake();
				}			
			}
		}
	}

	void Update(sol::state& lua) {
		for (auto entity : GetSystemEntities()) {
			const auto& script = entity.GetComponent<ScriptComponent>();
			lua["this"] = entity;
			script.update();
		}
	}
};
