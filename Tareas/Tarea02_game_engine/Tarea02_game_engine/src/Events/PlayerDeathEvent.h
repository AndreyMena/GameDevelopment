#pragma once
#include "../EventManager/Event.h"
#include "../ECS/ECS.h"

class PlayerDeathEvent : public Event {
public:
	Entity a;

	PlayerDeathEvent(Entity a) : a(a) {}
};
