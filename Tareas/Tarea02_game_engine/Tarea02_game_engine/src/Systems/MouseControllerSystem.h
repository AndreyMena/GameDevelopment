#pragma once


#include "../Components/MouseControllerComponent.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/MouseMotionEvent.h"

#include <iostream>
#include <memory>
#include <glm/glm.hpp>

class MouseControllerSystem : public System {
public:
	MouseControllerSystem() {
		RequireComponent<MouseControllerComponent>();
	}

	void SubscribeToMouseMotionEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<MouseControllerSystem, MouseMotionEvent>(
			this, &MouseControllerSystem::OnMouseMotionEvent);
	}

	void OnMouseMotionEvent(MouseMotionEvent& e) {
		std::cout << "(" << e.position.x << "," << e.position.y << std::endl;
	}
};

