#pragma once

#include <glm/glm.hpp>

enum PlayerState { idle, jump, fall, run };

struct PlayerDataComponent {
	PlayerState state = PlayerState::idle;

	bool jump = false;
	bool left = false;
	bool right = false;

	bool canJump = true;

	PlayerDataComponent() {}
};