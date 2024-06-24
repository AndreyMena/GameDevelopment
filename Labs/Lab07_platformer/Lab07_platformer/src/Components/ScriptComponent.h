#pragma once

#include <sol/sol.hpp>

struct ScriptComponent {
	sol::function update;
	sol::function onCollision;

	ScriptComponent(sol::function update = sol::lua_nil,
		sol::function onCollision = sol::lua_nil) {
		this->update = update;
		this->onCollision = onCollision;
	}
};