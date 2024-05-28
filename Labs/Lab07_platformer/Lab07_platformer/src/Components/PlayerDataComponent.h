#pragma once

#include <glm/glm.hpp>

enum PlayerState { idle, jump, fall, run };

struct PlayerDataComponent {
	PlayerState state = PlayerState::idle;

	bool jump = false;
	bool left = false;
	bool right = false;

	bool canJump = true;

	glm::vec2 jumpForce;
	float runningSpeed;

	PlayerDataComponent(glm::vec2 jumpForce = glm::vec2(0), 
		float runningSpeed = 0) {
		this->jumpForce = jumpForce;
		this->runningSpeed = runningSpeed;
	}
};