#pragma once

#include "../Components/RigidbodyComponent.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/KeyboardEvent.h"
#include "../Events/ActionEvent.h"
#include "../KeyActionMap/KeyActionMap.h"
#include <glm/glm.hpp>
#include <memory>
#include <iostream>

class KeyboardControllerSystem : public System {
	std::shared_ptr<EventManager> eventManager = nullptr;
	std::shared_ptr<KeyActionMap> keyActionMap = nullptr;

public:
	KeyboardControllerSystem(const std::shared_ptr<EventManager>& eventManager,
		const std::shared_ptr<KeyActionMap>& keyActionMap) {
		this->eventManager = eventManager;
		this->keyActionMap = keyActionMap;

	}
	//~KeyboardControllerSystem();

	void SubscribeToKeyboardEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<KeyboardControllerSystem, KeyboardEvent>(
			this, &KeyboardControllerSystem::OnKeyboardEvent);
	}

	void OnKeyboardEvent(KeyboardEvent& e) {
		if (e.keyDown) {
			if (keyActionMap->IskeyMapped(e.keyCode)) {
				std::cout << keyActionMap->GetAction(e.keyCode) << std::endl;
				eventManager->EmitteEvent<ActionEvent>(keyActionMap->GetAction(
					e.keyCode), true);
			}
		}else{
			if (keyActionMap->IskeyMapped(e.keyCode)) {
				eventManager->EmitteEvent<ActionEvent>(keyActionMap->GetAction(
					e.keyCode), false);
			}
		}
	}
};
