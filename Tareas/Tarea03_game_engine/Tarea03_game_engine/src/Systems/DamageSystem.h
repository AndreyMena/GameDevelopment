#pragma once

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/CollisionEvent.h"
#include <memory>

class DamageSystem : public System {
public:
	DamageSystem() {}

	void SubscribeToCollisionEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<DamageSystem, CollisionEvent>(this,
			&DamageSystem::OnCollisionEvent);
	}

	void OnCollisionEvent(CollisionEvent& e) {
		e.a.Kill();
		e.b.Kill();
	}
};