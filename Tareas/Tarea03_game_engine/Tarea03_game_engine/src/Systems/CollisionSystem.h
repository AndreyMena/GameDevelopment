#pragma once

#include "../Components/ScriptComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/CollisionEvent.h"

#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <sol/sol.hpp>

class CollisionSystem : public System {
	bool CheckAABBCollision(float aX, float aY, float aW, float aH, float bX,
		float bY, float bW, float bH) {
		
		bool collision = (
			aX < bX + bW &&
			aX + aW > bX &&
			aY < bY + bW &&
			aY + aH > bY
			);
		return collision;
	}
public:
	CollisionSystem() {
		RequireComponent<BoxColliderComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(const std::shared_ptr<EventManager>& eventManager, 
		sol::state& lua) {
		auto entities = GetSystemEntities();

		for (auto it = entities.begin(); it != entities.end(); it++) {
			auto a = *it;
			auto& aCollider = a.GetComponent<BoxColliderComponent>();
			auto& aTransform = a.GetComponent<TransformComponent>();

			for (auto jt = it; jt != entities.end(); jt++) {
				auto b = *jt;

				if (a == b) { continue; }

				auto& bCollider = b.GetComponent<BoxColliderComponent>();
				auto& bTransform = b.GetComponent<TransformComponent>();

				bool collision = CheckAABBCollision(
					aTransform.position.x,
					aTransform.position.y,
					static_cast<float>(aCollider.width),
					static_cast<float>(aCollider.height),
					bTransform.position.x,
					bTransform.position.y,
					static_cast<float>(bCollider.width),
					static_cast<float>(bCollider.height)
				);

				if (collision) {
					//Esta barrera es solo para enemigos o bosses
					if ((a.GetTag() == "player" && b.GetTag() == "barrier") || 
						b.GetTag() == "player" && a.GetTag() == "barrier") {
						return;
					}
					if ((a.GetTag() == "player" && b.GetTag() == "playerbarrier") ||
						b.GetTag() == "player" && a.GetTag() == "playerbarrier") {
						return;
					}
					if ((a.GetTag() == "arrow" && b.GetTag() == "barrier") ||
						b.GetTag() == "arrow" && a.GetTag() == "barrier") {
						return;
					}
					eventManager->EmitteEvent<CollisionEvent>(a, b);

					if (a.HasComponent<ScriptComponent>()) {
						const auto& script = a.GetComponent<ScriptComponent>();
						if (script.onCollision != sol::nil) {
							lua["this"] = a;
							script.onCollision(b);
						}
					}
					if (b.HasComponent<ScriptComponent>()) {
						const auto& script = b.GetComponent<ScriptComponent>();
						if (script.onCollision != sol::nil) {
							lua["this"] = b;
							script.onCollision(a);
						}
					}
				}
			}
		}
	}
};