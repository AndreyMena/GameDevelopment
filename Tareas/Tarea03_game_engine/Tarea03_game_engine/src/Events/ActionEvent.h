#pragma once

#include "../EventManager/Event.h"
#include <string>

class ActionEvent : public Event {
public:
	std::string action;
	bool isActive;

	ActionEvent(const std::string& action, bool isActive) {
		this->action = action;
		this->isActive = isActive;
	}
};

