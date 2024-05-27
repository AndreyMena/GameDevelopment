#pragma once

#include "../ECS/ECS.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"
#include <glm/glm.hpp>

class MovementSystem : public System {
public:
	MovementSystem() {
		RequireComponent<RigidbodyComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(double deltaTyme) {
		for (auto entity : GetSystemEntities()) {
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
			auto& transform = entity.GetComponent<TransformComponent>();

			if (rigidbody.isStatic) { continue; }

			rigidbody.acceleration = rigidbody.sumForces * rigidbody.invMass;
			rigidbody.velocity += rigidbody.acceleration * static_cast<float>(deltaTyme);

			transform.previousPosition = transform.position;
			transform.position += rigidbody.velocity * static_cast<float>(deltaTyme);

			rigidbody.sumForces = glm::vec2(0);
		}
	}
};
