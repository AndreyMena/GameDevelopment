#pragma once

#include <string>
#include <glm/glm.hpp>

struct RigidbodyComponent {
	glm::vec2 velocity;

	RigidbodyComponent(glm::vec2 velocity = glm::vec2(0)) {
		this->velocity = velocity;
	}
};