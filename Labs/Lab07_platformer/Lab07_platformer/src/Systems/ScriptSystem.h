#pragma once

#include "../Bindings/LuaBindings.h"
#include "../ECS/ECS.h"
#include "../Components/ScriptComponent.h"

#include <iostream>
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
	}

	void Update(sol::state& lua) {
		for (auto entity : GetSystemEntities()) {
			const auto& script = entity.GetComponent<ScriptComponent>();
			lua["this"] = entity;
			script.update();
		}
	}
};
