#pragma once

#include "../ECS/ECS.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"

class MovementSystem : public System {
public:
	MovementSystem() {
		RequireComponent<RigidbodyComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(float deltaTyme) {
		for (auto entity : GetSystemEntities()) {
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
			auto& transform = entity.GetComponent<TransformComponent>();

			transform.position += rigidbody.velocity * deltaTyme;
		}
	}
};
