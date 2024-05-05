#pragma once
#include "../EventManager/Event.h"
#include "../ECS/ECS.h"

class OutOfLimitEvent : public Event {
public:
	Entity bullet;

	OutOfLimitEvent(Entity bullet) : bullet(bullet) {}
};
