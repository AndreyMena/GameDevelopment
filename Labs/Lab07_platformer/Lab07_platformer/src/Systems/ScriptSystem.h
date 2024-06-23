#pragma once

#include "../Bindings/LuaBindings.h"
#include "../ECS/ECS.h"
#include "../Components/ScriptComponent.h"

class ScriptSystem : public System {
public:
	ScriptSystem() {
		RequireComponent<ScriptComponent>();
	}
	
	void CreateLuaBindings(sol::state& lua) {
		lua.set_function("get_action_state",  GetActionState);
	}

	void Update() {
		for (auto entity : GetSystemEntities()) {
			const auto& script = entity.GetComponent<ScriptComponent>();
			script.update();
		}
	}
};
