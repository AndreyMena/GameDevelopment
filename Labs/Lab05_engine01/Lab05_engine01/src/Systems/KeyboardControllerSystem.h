#pragma once

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/KeyboardEvent.h"
#include <memory>
#include <iostream>

class KeyboardControllerSystem : public System {
public:
	KeyboardControllerSystem() {
		// TODO agregar los componentes q requiere
	}
	//~KeyboardControllerSystem();

	void SubscribeToKeyboardEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<KeyboardControllerSystem, KeyboardEvent>(
			this, &KeyboardControllerSystem::OnKeyboardEvent);
	}

	void OnKeyboardEvent(KeyboardEvent& e) {
		if (e.keyDown) {
			if (e.keyCode == SDLK_w) {
				std::cout << "Tecla W: ABAJO" << std::endl;
			}
			if (e.keyCode == SDLK_d) {
				std::cout << "Tecla D: ABAJO" << std::endl;
			}
			if (e.keyCode == SDLK_s) {
				std::cout << "Tecla S: ABAJO" << std::endl;
			}
			if (e.keyCode == SDLK_a) {
				std::cout << "Tecla A: ABAJO" << std::endl;
			}
		}else{
			if (e.keyCode == SDLK_w) {
				std::cout << "Tecla W: ARRIBA" << std::endl;
			}
			if (e.keyCode == SDLK_d) {
				std::cout << "Tecla D: ARRIBA" << std::endl;
			}
			if (e.keyCode == SDLK_s) {
				std::cout << "Tecla S: ARRIBA" << std::endl;
			}
			if (e.keyCode == SDLK_a) {
				std::cout << "Tecla A: ARRIBA" << std::endl;
			}
		}
	}
};
