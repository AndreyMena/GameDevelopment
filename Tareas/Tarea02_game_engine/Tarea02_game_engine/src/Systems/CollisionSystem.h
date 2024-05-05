#pragma once

#include "../Components/CircleColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"
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

	void Update(std::shared_ptr<EventManager>& eventManager) {
		auto entities = GetSystemEntities();

		for (auto i = entities.begin(); i != entities.end(); i++) {
			auto a = *i;
			auto& aCollider = a.GetComponent<CircleColliderComponent>();
			auto& aTransform = a.GetComponent<TransformComponent>();
			for (auto j = i; j != entities.end(); j++) {
				auto b = *j;

				if (a == b) {
					continue;
				}
				auto& aTag = a.GetComponent<TagComponent>();
				auto& bTag = b.GetComponent<TagComponent>();
				if (aTag.tag == 0 && bTag.tag == 2) {
					continue;  //Player vs Bullet continue
				}
				if (aTag.tag == 2 && bTag.tag == 2) {
					continue;  //Bullet vs Bullet continue
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
