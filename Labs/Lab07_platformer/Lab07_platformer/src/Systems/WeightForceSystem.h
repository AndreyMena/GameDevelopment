#pragma once

#include "../Components/RigidbodyComponent.h"
#include "../ECS/ECS.h"

#include <glm/glm.hpp>

class WeightForceSystem : public System {
public:
	WeightForceSystem() {
		RequireComponent<RigidbodyComponent>();
	}

	void Update() {
		for (auto entity : GetSystemEntities()) {
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();

			if (rigidbody.isStatic) { continue; }

			rigidbody.sumForces += glm::vec2(0.f, 9.8 * rigidbody.mass * 64);
		}
	}
};
