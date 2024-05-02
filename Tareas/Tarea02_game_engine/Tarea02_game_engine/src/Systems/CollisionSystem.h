#pragma once

#include "../Components/CircleColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../EventManager/EventManager.h"
#include "../ECS/ECS.h"
#include "../Events/CollisionEvent.h"
#include <glm/glm.hpp>
#include <memory>
#include <iostream>

class CollisionSystem : public System {
	bool CheckCircleCollision(float aRadius, glm::vec2 aCenter, float bRadius, 
		glm::vec2 bCenter) {
		
		glm::vec2 diff = aCenter - bCenter;
		float length = glm::length(diff);

		return (aRadius + bRadius) >= length;
	}

public:
	CollisionSystem() {
		RequireComponent<CircleColliderComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(std::shared_ptr<EventManager>& eventManager, size_t windowWidth, size_t windowHeight) {
		auto entities = GetSystemEntities();

		for (auto entity : GetSystemEntities()) {
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();

			
			//Verificacion de rebotes
			if (entity.GetId() != 0) {
				if (transform.position.x + sprite.width >= windowWidth
					|| transform.position.x <= 0.0) {
					rigidbody.velocity.x = rigidbody.velocity.x * -1;
				}
				if (transform.position.y + sprite.height >= windowHeight
					|| transform.position.y <= 0.0) {
					rigidbody.velocity.y = rigidbody.velocity.y * -1;
				}
			}
		}

		for (auto i = entities.begin(); i != entities.end(); i++) {
			auto a = *i;
			auto& aCollider = a.GetComponent<CircleColliderComponent>();
			auto& aTransform = a.GetComponent<TransformComponent>();
			for (auto j = i; j != entities.end(); j++) {
				auto b = *j;

				if (a == b) {
					continue;
				}

				auto& bCollider = b.GetComponent<CircleColliderComponent>();
				auto& bTransform = b.GetComponent<TransformComponent>();
				
				glm::vec2 aCenter = glm::vec2(
					aTransform.position.x + 16,
					aTransform.position.y + 16
				);

				glm::vec2 bCenter = glm::vec2(
					bTransform.position.x + 16,
					bTransform.position.y + 16
				);

				bool collision = CheckCircleCollision(aCollider.radius, aCenter, 
					bCollider.radius, bCenter);

				if (collision) {
					std::cout << a.GetId() << " colisiona con " << b.GetId() << std::endl;
					eventManager->EmitteEvent<CollisionEvent>(a, b);
				}
			}
		}
	}
};
