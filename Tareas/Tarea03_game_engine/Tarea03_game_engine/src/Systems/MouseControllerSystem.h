#pragma once

#include "../Game/Game.h"
#include "../Components/MouseControllerComponent.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/MouseMotionEvent.h"
#include "../Events/MouseClickEvent.h"

#include <iostream>
#include <memory>
#include <glm/glm.hpp>

class MouseControllerSystem : public System {
public:
	MouseControllerSystem() {
		//RequireComponent<MouseControllerComponent>();
	}

	void SubscribeToMouseMotionEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<MouseControllerSystem, MouseMotionEvent>(
			this, &MouseControllerSystem::OnMouseMotionEvent);
	}

	void SubscribeToMouseClickEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<MouseControllerSystem, MouseClickEvent>(
			this, &MouseControllerSystem::OnMouseClickEvent);
	}

	void OnMouseClickEvent(MouseClickEvent& e) {
		std::cout << "(" << e.position.x << "," << e.position.y << std::endl;
		if (e.position.x >= 281 && e.position.y >= 150 && 
			e.position.x <= 492 && e.position.y <= 183) {
			std::cout << "Jugar" << std::endl;
			Game::GetInstance().isPlaying = true;
		}
		if (e.position.x >= 181 && e.position.y >= 201 &&
			e.position.x <= 594 && e.position.y <= 235) {
			std::cout << "Como jugar" << std::endl;
		}
		if (e.position.x >= 300 && e.position.y >= 254 &&
			e.position.x <= 470 && e.position.y <= 288) {

			Game::GetInstance().isRunning = false;
			std::cout << "Salir" << std::endl;
		}
	}

	void OnMouseMotionEvent(MouseMotionEvent& e) {
		//std::cout << "(" << e.position.x << "," << e.position.y << std::endl;
	}
};

