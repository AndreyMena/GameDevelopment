#pragma once

#include <glm/glm.hpp>
#include "../EventManager/Event.h"

class MouseClickEvent : public Event {
public:
	glm::vec2 position;

	MouseClickEvent(glm::vec2 position = glm::vec2(0)) {
		this->position = position;
	}
};
