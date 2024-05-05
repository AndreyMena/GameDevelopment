#pragma once

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/MouseClickEvent.h"
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/SpriteComponent.h"
#include <memory>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>

class ProjectileEmitterSystem : public System {
	std::shared_ptr<ECSManager>& manager;
public:
	ProjectileEmitterSystem(std::shared_ptr<ECSManager>& manager) : manager(manager) {
		RequireComponent<ProjectileEmitterComponent>();
	}

	void SubscribeToMouseClickEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<ProjectileEmitterSystem, MouseClickEvent>(this,
			&ProjectileEmitterSystem::OnMouseClickEvent);
	}

	void OnMouseClickEvent(MouseClickEvent& e) {
		auto entities = GetSystemEntities();
		auto entity = entities[0];  // Player

		auto& transform = entity.GetComponent<TransformComponent>();
		auto& projectile = entity.GetComponent<ProjectileEmitterComponent>();
		auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
		auto& sprite = entity.GetComponent<SpriteComponent>();

		double distance = sqrt(pow(e.position.x - transform.position.x, 2) 
			+ pow(e.position.y - transform.position.y, 2));

		double time = distance / projectile.speed;

		glm::vec2 direccion;
		direccion.x = (e.position.x - transform.position.x) / time;
		direccion.y = (e.position.y - transform.position.y) / time;

		//rigidbody = direccion;
		std::cout <<"Dir: " << direccion.x << " " << direccion.y << std::endl;

		
		Entity enemy = manager->CreateEntity();
		//enemy.AddComponent<CircleColliderComponent>(16.0f);
		enemy.AddComponent<RigidbodyComponent>(glm::vec2(direccion.x, direccion.y), projectile.speed);
		enemy.AddComponent<SpriteComponent>(projectile.assetId, 16.0f, 16.0f, 0.0f, 0);
		glm::vec2 pos;
		pos.x = transform.position.x;
		pos.y = transform.position.y;
		enemy.AddComponent<TransformComponent>(pos,
			glm::vec2(2, 2), 0);
	}
};
