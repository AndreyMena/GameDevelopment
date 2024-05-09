#pragma once
#include "../EventManager/Event.h"
#include "../ECS/ECS.h"

class EnemyKilledEvent : public Event {
public:
	Entity a;

	EnemyKilledEvent(Entity a) : a(a) {}
};
