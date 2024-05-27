#pragma once

#include "../Components/BoxColliderComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/CollisionEvent.h"

#include <glm/glm.hpp>
#include <memory>
#include <iostream>

class OverlapSystem : public System {
	bool CheckTopCollision(Entity a, Entity b) {
		auto& aCollider = a.GetComponent<BoxColliderComponent>();
		auto& aTransform= a.GetComponent<TransformComponent>();
		auto& bCollider = b.GetComponent<BoxColliderComponent>();
		auto& bTransform= b.GetComponent<TransformComponent>();
		
		float aX = aTransform.previousPosition.x;
		float aY = aTransform.previousPosition.y;
		float aW = static_cast<float>(aCollider.width);
		
		float bX = bTransform.previousPosition.x;
		float bY = bTransform.previousPosition.y;
		float bW = static_cast<float>(bCollider.width);

		return (
			aX < bX + bW &&
			aX + aW > bX &&
			aY > bY
		);
	}

	void AvoidOverlap(Entity eStatic, Entity eDynamic) {
		auto& aCollider = eStatic.GetComponent<BoxColliderComponent>();
		auto& aTransform = eStatic.GetComponent<TransformComponent>();
		
		auto& bCollider = eDynamic.GetComponent<BoxColliderComponent>();
		auto& bTransform = eDynamic.GetComponent<TransformComponent>();
		auto& bRigidbody= eDynamic.GetComponent<RigidbodyComponent>();

		if (CheckTopCollision(eStatic, eDynamic)) {
			bTransform.position = glm::vec2(bTransform.position.x,
				aTransform.position.y - bCollider.height);
			bRigidbody.velocity = glm::vec2(bRigidbody.velocity.x, 0.0f);

			bRigidbody.onGround = true;
		}
	}

public:
	OverlapSystem() {
		RequireComponent<BoxColliderComponent>();
		RequireComponent<TransformComponent>();
	}

	void SubscribeToCollisionEvent(
		const std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<OverlapSystem, CollisionEvent>(this,
			&OverlapSystem::OnCollisionEvent);
	}

	void OnCollisionEvent(CollisionEvent& e) {
		auto& aRigidbody= e.a.GetComponent<RigidbodyComponent>();
		auto& bRigidbody= e.b.GetComponent<RigidbodyComponent>();

		if (!bRigidbody.isStatic) {
			AvoidOverlap(e.a, e.b);
		}
		if (!aRigidbody.isStatic) {
			AvoidOverlap(e.b, e.a);
		}
	}
};
