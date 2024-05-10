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
			std::cout << multiShot.timeSinceLastUse << std::endl;
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

		Entity bullet1 = manager->CreateEntity();
		bullet1.AddComponent<CircleColliderComponent>(16.0f);
		bullet1.AddComponent<RigidbodyComponent>(glm::vec2(0, -300), -50);
		bullet1.AddComponent<SpriteComponent>(multiShot.assetId, 32.0f, 32.0f, 96.0f, 128.0f);
		bullet1.AddComponent<TransformComponent>(
			glm::vec2(transform.position.x, transform.position.y),
			glm::vec2(2, 2), 0);
		bullet1.AddComponent<TagComponent>(2);

		Entity bullet2 = manager->CreateEntity();
		bullet2.AddComponent<CircleColliderComponent>(16.0f);
		bullet2.AddComponent<RigidbodyComponent>(glm::vec2(300, 0), 10);
		bullet2.AddComponent<SpriteComponent>(multiShot.assetId, 32.0f, 32.0f, 96.0f, 128.0f);
		bullet2.AddComponent<TransformComponent>(
			glm::vec2(transform.position.x, transform.position.y),
			glm::vec2(2, 2), 90);
		bullet2.AddComponent<TagComponent>(2);

		Entity bullet3 = manager->CreateEntity();
		bullet3.AddComponent<CircleColliderComponent>(16.0f);
		bullet3.AddComponent<RigidbodyComponent>(glm::vec2(0, 300), 10);
		bullet3.AddComponent<SpriteComponent>(multiShot.assetId, 32.0f, 32.0f, 96.0f, 128.0f);
		bullet3.AddComponent<TransformComponent>(
			glm::vec2(transform.position.x, transform.position.y),
			glm::vec2(2, 2), 180);
		bullet3.AddComponent<TagComponent>(2);

		Entity bullet4 = manager->CreateEntity();
		bullet4.AddComponent<CircleColliderComponent>(16.0f);
		bullet4.AddComponent<RigidbodyComponent>(glm::vec2(-300, 0), 10);
		bullet4.AddComponent<SpriteComponent>(multiShot.assetId, 32.0f, 32.0f, 96.0f, 128.0f);
		bullet4.AddComponent<TransformComponent>(
			glm::vec2(transform.position.x, transform.position.y),
			glm::vec2(2, 2), 270);
		bullet4.AddComponent<TagComponent>(2);

		Entity bullet5 = manager->CreateEntity();
		bullet5.AddComponent<CircleColliderComponent>(16.0f);
		bullet5.AddComponent<RigidbodyComponent>(glm::vec2(-175, 175), 10);
		bullet5.AddComponent<SpriteComponent>(multiShot.assetId, 32.0f, 32.0f, 96.0f, 128.0f);
		bullet5.AddComponent<TransformComponent>(
			glm::vec2(transform.position.x, transform.position.y),
			glm::vec2(2, 2), 225);
		bullet5.AddComponent<TagComponent>(2);

		Entity bullet6 = manager->CreateEntity();
		bullet6.AddComponent<CircleColliderComponent>(16.0f);
		bullet6.AddComponent<RigidbodyComponent>(glm::vec2(175, 175), 10);
		bullet6.AddComponent<SpriteComponent>(multiShot.assetId, 32.0f, 32.0f, 96.0f, 128.0f);
		bullet6.AddComponent<TransformComponent>(
			glm::vec2(transform.position.x, transform.position.y),
			glm::vec2(2, 2), 135);
		bullet6.AddComponent<TagComponent>(2);

		Entity bullet7 = manager->CreateEntity();
		bullet7.AddComponent<CircleColliderComponent>(16.0f);
		bullet7.AddComponent<RigidbodyComponent>(glm::vec2(175, -175), 10);
		bullet7.AddComponent<SpriteComponent>(multiShot.assetId, 32.0f, 32.0f, 96.0f, 128.0f);
		bullet7.AddComponent<TransformComponent>(
			glm::vec2(transform.position.x, transform.position.y),
			glm::vec2(2, 2), 45);
		bullet7.AddComponent<TagComponent>(2);

		Entity bullet8 = manager->CreateEntity();
		bullet8.AddComponent<CircleColliderComponent>(16.0f);
		bullet8.AddComponent<RigidbodyComponent>(glm::vec2(-175, -175), 10);
		bullet8.AddComponent<SpriteComponent>(multiShot.assetId, 32.0f, 32.0f, 96.0f, 128.0f);
		bullet8.AddComponent<TransformComponent>(
			glm::vec2(transform.position.x, transform.position.y),
			glm::vec2(2, 2), 315);
		bullet8.AddComponent<TagComponent>(2);

	}
};

