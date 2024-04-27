#pragma once
#include "../EventManager/Event.h"
#include "../ECS/ECS.h"

class CollisionEvent : public Event{
public:
	Entity a;
	Entity b;

	CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
};
