#pragma once

#include <sol/sol.hpp>

struct ScriptComponent {
	sol::function awake;
	sol::function update;
	sol::function onCollision;

	ScriptComponent(sol::function awake = sol::lua_nil, 
		sol::function update = sol::lua_nil,
		sol::function onCollision = sol::lua_nil) {
		this->awake = awake;
		this->update = update;
		this->onCollision = onCollision;
	}
};