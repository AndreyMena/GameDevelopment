#pragma once

#include <glm/glm.hpp>

struct TransformComponent {
	glm::vec2 previousPosition;
	glm::vec2 position;
	glm::vec2 scale;
	double rotation;

	TransformComponent(glm::vec2 position = glm::vec2(0), 
		glm::vec2 scale = glm::vec2(1.0f, 1.0f), double rotation = 0) {
		this->previousPosition = position;
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
	}
};