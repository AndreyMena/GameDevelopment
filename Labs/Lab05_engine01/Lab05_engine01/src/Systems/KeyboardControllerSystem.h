#pragma once

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/KeyboardEvent.h"
#include "../Components/KeyboardControllerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include <glm/glm.hpp>
#include <memory>
#include <iostream>

class KeyboardControllerSystem : public System {
public:
	KeyboardControllerSystem() {
		RequireComponent<KeyboardControllerComponent>();
		RequireComponent<RigidbodyComponent>();
	}
	//~KeyboardControllerSystem();

	void SubscribeToKeyboardEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<KeyboardControllerSystem, KeyboardEvent>(
			this, &KeyboardControllerSystem::OnKeyboardEvent);
	}

	void OnKeyboardEvent(KeyboardEvent& e) {
		auto entities = GetSystemEntities();
		auto entity = entities[0];  // Player
		auto& controller = entity.GetComponent<KeyboardControllerComponent>();
		auto& rigidbody = entity.GetComponent<RigidbodyComponent>();

		if (e.keyDown) {
			if (e.keyCode == SDLK_w) {
				controller.up = true;
			}
			if (e.keyCode == SDLK_d) {
				controller.right = true;
			}
			if (e.keyCode == SDLK_s) {
				controller.down = true;
			}
			if (e.keyCode == SDLK_a) {
				controller.left = true;
			}
		}else{
			if (e.keyCode == SDLK_w) {
				controller.up = false;
			}
			if (e.keyCode == SDLK_d) {
				controller.right = false;
			}
			if (e.keyCode == SDLK_s) {
				controller.down = false;
			}
			if (e.keyCode == SDLK_a) {
				controller.left = false;
			}
		}

		rigidbody.velocity = glm::vec2(0);

		if (controller.up) {
			rigidbody.velocity.y += -rigidbody.speed;
		}
		if (controller.right) {
			rigidbody.velocity.x += rigidbody.speed;
		}
		if (controller.down) {
			rigidbody.velocity.y += rigidbody.speed;
		}
		if (controller.left) {
			rigidbody.velocity.x += -rigidbody.speed;
		}

	}
};
