#pragma once


#include "../Components/MouseControllerComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/MouseMotionEvent.h"

#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <cmath>

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
		auto entities = GetSystemEntities();
		auto entity = entities[0];  // Player

		auto& controller = entity.GetComponent<MouseControllerComponent>();
		auto& transform = entity.GetComponent<TransformComponent>();
		auto& sprite = entity.GetComponent<SpriteComponent>();
		controller.coordinates.x = e.position.x;
		controller.coordinates.y = e.position.y;

		glm::vec2 coordsTemp;
		coordsTemp.x = (controller.coordinates.x - (transform.position.x + ((sprite.width * transform.scale.x) / 2)));
		coordsTemp.y = (controller.coordinates.y - (transform.position.y + ((sprite.height * transform.scale.y) / 2)));

		double angleRadians = atan2(coordsTemp.y, coordsTemp.x);
		double angleDegree = (angleRadians * 180.0 / M_PI);
		angleDegree += 90;  // Rotacion de la imagen

		if (angleDegree < 0) {
			angleDegree = fmod((angleDegree + 360), 360);  // Ajustar el ángulo a un rango de 0 a 360 grados
		}
		transform.rotation = angleDegree;
	}
};

