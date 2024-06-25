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

enum Direction { top, left, bottom, right };

class OverlapSystem : public System {
	bool CheckDirectionCollision(Entity a, Entity b, Direction dir) {
		auto& aCollider = a.GetComponent<BoxColliderComponent>();
		auto& aTransform= a.GetComponent<TransformComponent>();
		auto& bCollider = b.GetComponent<BoxColliderComponent>();
		auto& bTransform= b.GetComponent<TransformComponent>();
		
		float aX = aTransform.previousPosition.x;
		float aY = aTransform.previousPosition.y;
		float aW = static_cast<float>(aCollider.width);
		float aH = static_cast<float>(aCollider.height);

		float bX = bTransform.previousPosition.x;
		float bY = bTransform.previousPosition.y;
		float bW = static_cast<float>(bCollider.width);
		float bH = static_cast<float>(bCollider.height);

		bool direction = false;

		if (dir == Direction::top) {
			return (
				aX < bX + bW &&
				aX + aW > bX &&
				aY > bY
			);
		}
		if (dir == Direction::bottom) {
			return (
				aX < bX + bW &&
				aX + aW > bX &&
				aY < bY
			);
		}
		if (dir == Direction::left) {
			return (
				aY < bY + bH &&
				aY + aH > bY &&
				aX > bX
			);
		}
		if (dir == Direction::right) {
			return (
				aY < bY + bH &&
				aY + aH > bY &&
				aX < bX
			);
		}
		return false;
	}

	void AvoidOverlap(Entity eStatic, Entity eDynamic) {
		auto& aCollider = eStatic.GetComponent<BoxColliderComponent>();
		auto& aTransform = eStatic.GetComponent<TransformComponent>();
		
		auto& bCollider = eDynamic.GetComponent<BoxColliderComponent>();
		auto& bTransform = eDynamic.GetComponent<TransformComponent>();
		auto& bRigidbody= eDynamic.GetComponent<RigidbodyComponent>();

		if (CheckDirectionCollision(eStatic, eDynamic, Direction::top)) {
			bTransform.position = glm::vec2(bTransform.position.x,
				aTransform.position.y - bCollider.height);
			bRigidbody.velocity = glm::vec2(bRigidbody.velocity.x, 0.0f);
		}
		if (CheckDirectionCollision(eStatic, eDynamic, Direction::bottom)) {
			bTransform.position = glm::vec2(bTransform.position.x,
				aTransform.position.y + aCollider.height);
			bRigidbody.velocity = glm::vec2(bRigidbody.velocity.x, 0.0f);
		}
		if (CheckDirectionCollision(eStatic, eDynamic, Direction::right)) {
			bTransform.position = glm::vec2(aTransform.position.x + aCollider.width,
				bTransform.position.y);
			bRigidbody.velocity = glm::vec2(0.0f, bRigidbody.velocity.y);
		}
		if (CheckDirectionCollision(eStatic, eDynamic, Direction::left)) {
			bTransform.position = glm::vec2(aTransform.position.x - bCollider.width,
				bTransform.position.y);
			bRigidbody.velocity = glm::vec2(0.0f, bRigidbody.velocity.y);
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
