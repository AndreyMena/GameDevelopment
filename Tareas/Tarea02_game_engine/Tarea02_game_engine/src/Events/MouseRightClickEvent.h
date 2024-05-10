#pragma once

#include <glm/glm.hpp>
#include "../EventManager/Event.h"

class MouseRightClickEvent : public Event {
public:
	glm::vec2 position;

	MouseRightClickEvent(glm::vec2 position = glm::vec2(0)) {
		this->position = position;
	}
};
