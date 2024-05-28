#pragma once

#include <glm/glm.hpp>

struct PlayerDataComponent {
	bool jump = false;
	bool left = false;
	bool right = false;

	bool canJump = true;

	glm::vec2 jumpForce;

	PlayerDataComponent(glm::vec2 jumpForce = glm::vec2(0)) {
		this->jumpForce = jumpForce;
	}
};