#pragma once

#include "../Components/PlayerDataComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/ActionEvent.h"

#include <memory>

class PlayerActionSystem : public System {
public:
	PlayerActionSystem() {
		RequireComponent<PlayerDataComponent>();
		RequireComponent<RigidbodyComponent>();
	}

	void SubscribeToActionEvent(
		const std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<PlayerActionSystem, ActionEvent>(
			this, &PlayerActionSystem::OnActionEvent);
	}

	void OnActionEvent(ActionEvent& e) {
		auto player = GetSystemEntities()[0];

		auto& data = player.GetComponent<PlayerDataComponent>();
		auto& rigidbody = player.GetComponent<RigidbodyComponent>();

		if (e.action.compare("jump") == 0) {
			if (e.isActive) {
				data.jump = true;
			} else {
				data.jump = false;
				data.canJump = true;
			}
		}
		if (e.action.compare("move_right") == 0) {
			if (e.isActive) {
				data.right = true;
			} else {
				data.right = false;
			}
		}
		if (e.action.compare("move_left") == 0) {
			if (e.isActive) {
				data.left = true;
			} else {
				data.left = false;
			}
		}

		// Resolver accion
		if (data.jump) {
			///if (rigidbody.onGround && data.canJump) {
			if (data.canJump) {
				//rigidbody.sumForces += rigidbody.jumpForce;
				//rigidbody.onGround = false;
				data.canJump = false;
			}
		}
		rigidbody.velocity.x = 0;
		if (data.right) {
			//rigidbody.velocity.x += rigidbody.speed;
		}
		if (data.left) {
			//rigidbody.velocity.x += -rigidbody.speed;
		}
	}
};