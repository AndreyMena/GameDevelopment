#pragma once

#include "../EventManager/Event.h"
#include <string>

class LevelEvent : public Event {
public:
	std::string levelEvent;

	LevelEvent(std::string levelEvent) {
		this->levelEvent = levelEvent;
	}
};
