#pragma once

#include <string>
#include <glm/glm.hpp>

struct RigidbodyComponent {
	glm::vec2 velocity;
	float speed;

	RigidbodyComponent(glm::vec2 velocity = glm::vec2(0), float speed = 0) {
		this->velocity = velocity;
		this->speed = speed;
	}
};