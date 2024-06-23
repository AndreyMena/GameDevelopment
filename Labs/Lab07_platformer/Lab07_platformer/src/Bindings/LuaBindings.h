#pragma once

#include "../Components/RigidbodyComponent.h"
#include "../game/Game.h"

#include <glm/glm.hpp>
#include <string>
#include <tuple>

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

void SetVelocity(Entity entity, double x, double y) {
	// TODO:verificar si tiene rigidbody
	auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
	glm::vec2 velocity = glm::vec2(x, y);
	rigidbody.velocity = velocity;
}

std::tuple<double, double> GetVelocity(Entity entity) {
	// TODO:verificar si tiene rigidbody
	auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
	return std::make_tuple(rigidbody.velocity.x, rigidbody.velocity.y);
}