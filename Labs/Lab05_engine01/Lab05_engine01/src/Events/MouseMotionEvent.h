#pragma once

#include <glm/glm.hpp>
#include "../EventManager/Event.h"

class MouseMotionEvent : public Event {
public:
	glm::vec2 position;

	MouseMotionEvent(glm::vec2 position = glm::vec2(0)) {
		this->position = position;
	}
};
