#pragma once
#include <glm/glm.hpp>

struct MouseControllerComponent {
	glm::vec2 coordinates;

	MouseControllerComponent(glm::vec2 coordinates = glm::vec2(0)) 
		: coordinates(coordinates) {}
};