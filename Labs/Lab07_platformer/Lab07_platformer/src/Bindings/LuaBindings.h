#pragma once

#include "../AnimationManager/AnimationManager.h"
#include "../Components/AnimationComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
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

// SpriteComponent

void FlipSprite(Entity entity, bool flip) {
	auto& sprite = entity.GetComponent<SpriteComponent>();
	sprite.flip = flip;
}

// Animation and sprite function
void ChangeAnimation(Entity entity, const std::string& entityType, 
	const std::string& id) {
	auto& animation = entity.GetComponent<AnimationComponent>();
	auto& sprite = entity.GetComponent<SpriteComponent>();

	AnimationData animationData;
	animationData = Game::GetInstance().animationManager->GetAnimationData(
		entityType, id);

	sprite.assetId = animationData.spriteLabel; 
	sprite.width = animationData.widht;
	sprite.height = animationData.height;
	sprite.srcRect.x = 0;
	sprite.srcRect.y = 0;

	animation.currentFrame = animation.currentFrame;
	animation.frameSpeedRate = animation.frameSpeedRate;
	animation.numberOffFrames = animation.numberOffFrames;
	animation.isLoop = animation.isLoop;
	animation.startTime = SDL_GetTicks();
}
