#pragma once

#include "../Components/LifesComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/RespawnComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/CollisionEvent.h"
#include "../Events/EnemyKilledEvent.h"
#include <memory>

class DamageSystem : public System {
	std::shared_ptr<EventManager>& eventManager;
public:
	DamageSystem(std::shared_ptr<EventManager>& eventManager) : eventManager(eventManager) {
	}

	void SubscribeToCollisionEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<DamageSystem, CollisionEvent>(this,
			&DamageSystem::OnCollisionEvent);
	}

	void OnCollisionEvent(CollisionEvent& e) {
		if (e.a.GetComponent<TagComponent>().tag == 0) {
			auto& lifes = e.a.GetComponent<LifesComponent>();
			if (lifes.lifes > 0) {
				lifes.lifes = lifes.lifes - 1;
				auto& transform = e.a.GetComponent<TransformComponent>();
				auto& respawn = e.a.GetComponent<RespawnComponent>();
				transform.position = respawn.position;
			}else{
				e.a.Kill();
			}
		}else if (e.a.GetComponent<TagComponent>().tag == 1) {
			this->eventManager->EmitteEvent<EnemyKilledEvent>(e.a);
			e.a.Kill();
		}else{
			e.a.Kill();
		}
		if (e.b.GetComponent<TagComponent>().tag == 0) {
			auto& lifes = e.b.GetComponent<LifesComponent>();
			if (lifes.lifes > 0) {
				lifes.lifes = lifes.lifes - 1;
				auto& transform = e.a.GetComponent<TransformComponent>();
				auto& respawn = e.a.GetComponent<RespawnComponent>();
				transform.position = respawn.position;
			}else{
				e.b.Kill();
			}
		}else if (e.b.GetComponent<TagComponent>().tag == 1) {
			this->eventManager->EmitteEvent<EnemyKilledEvent>(e.b);
			e.b.Kill();
		}
	}
};