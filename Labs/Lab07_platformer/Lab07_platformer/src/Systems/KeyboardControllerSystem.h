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

		}else{

		}
	}
};
