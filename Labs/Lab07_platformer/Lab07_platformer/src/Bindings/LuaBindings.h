#pragma once

#include "../game/Game.h"
#include "../Components/RigidbodyComponent.h"

#include <glm/glm.hpp>
#include <string>

// Controllers
bool GetActionState(const std::string action) {
	return Game::GetInstance().controllerManager->GetActionState(action);
	
}

// RigidbodyComponent
void AddForce(Entity entity, double x, double y) {
	// TODO: verificar si tine rigidbody
	auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
	glm::vec2 force = glm::vec2(x, y);
	rigidbody.sumForces += force;
}

