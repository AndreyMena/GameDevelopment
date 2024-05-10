#pragma once


#include "../Components/MouseControllerComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/MultiShotComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TagComponent.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/MouseRightClickEvent.h"

#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <cmath>
#include <utility>
#include <map>

class MultiShotSystem : public System {
	std::shared_ptr<ECSManager>& manager;
public:
	MultiShotSystem(std::shared_ptr<ECSManager>& manager) : manager(manager) {
		RequireComponent<MultiShotComponent>();
	}

	void SubscribeToMouseRightClickEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<MultiShotSystem, MouseRightClickEvent>(
			this, &MultiShotSystem::OnMouseRightClickEvent);
	}

	void OnMouseRightClickEvent(MouseRightClickEvent& e) {
		auto entities = GetSystemEntities();
		auto entity = entities[0];  // Player
		auto& multiShot = entity.GetComponent<MultiShotComponent>();

		if (multiShot.timeSinceLastUse >= (multiShot.timeLimitPerUse / 1000)) {
			SpawnMultiShot(this->manager, multiShot); // Función para generar un nuevo enemigo
			multiShot.timeSinceLastUse = 0; // Reinicia el contador
		}
	}

	void Update(float deltaTime, std::shared_ptr<ECSManager>& manager) {
		for (auto entity : GetSystemEntities()) {
			auto& multiShot = entity.GetComponent<MultiShotComponent>();
			// Actualiza el tiempo transcurrido desde el último spawn de enemigo
			multiShot.timeSinceLastUse += deltaTime;
		}
	}

	void SpawnMultiShot(std::shared_ptr<ECSManager>& manager, MultiShotComponent& multiShot) {
		auto entities = GetSystemEntities();
		auto entity = entities[0];  // Player
		auto& transform = entity.GetComponent<TransformComponent>();

		std::map<int, std::pair<int, int>> map;
		map.emplace(1, std::pair<int, int>(0, -300));
		map.emplace(2, std::pair<int, int>(175, -175));
		map.emplace(3, std::pair<int, int>(300, 0));
		map.emplace(4, std::pair<int, int>(175, 175));
		map.emplace(5, std::pair<int, int>(0, 300));
		map.emplace(6, std::pair<int, int>(-175, 175));
		map.emplace(7, std::pair<int, int>(-300, 0));
		map.emplace(8, std::pair<int, int>(-175, -175));

		int rotation = 0;
		for (int i = 1; i <= 8; i++) {
			Entity entity = manager->CreateEntity();
			entity.AddComponent<CircleColliderComponent>(16.0f);
			entity.AddComponent<RigidbodyComponent>(glm::vec2(map[i].first, map[i].second), -50);
			entity.AddComponent<SpriteComponent>(multiShot.assetId, 32.0f, 32.0f, 96.0f, 128.0f);
			entity.AddComponent<TransformComponent>(
				glm::vec2(transform.position.x, transform.position.y),
				glm::vec2(2, 2), rotation);
			entity.AddComponent<TagComponent>(2);
			rotation += 45;
		}
	}
};

