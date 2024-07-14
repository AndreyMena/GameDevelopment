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
		auto& animationA = e.a.GetComponent<AnimationComponent>();
		auto& animationB = e.b.GetComponent<AnimationComponent>();
		animationA.lifes--;
		animationB.lifes--;
		if (animationA.lifes <= 0) {
			e.a.Kill();
		}
		if (animationB.lifes <= 0) {
			e.b.Kill();
		}
	}
};