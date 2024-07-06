#pragma once

#include <glm/glm.hpp>
#include "../EventManager/Event.h"

class ProjectileEvent : public Event {
public:
	glm::vec2 position;

	ProjectileEvent(glm::vec2 position = glm::vec2(0)) {
		this->position = position;
	}
};
