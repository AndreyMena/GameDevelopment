#pragma once

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/MouseClickEvent.h"
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"
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
		auto& sprite = entity.GetComponent<SpriteComponent>();
		auto& projectile = entity.GetComponent<ProjectileEmitterComponent>();
		auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
		auto& controller = entity.GetComponent<MouseControllerComponent>();

		double distance = sqrt(pow(e.position.x - transform.position.x, 2) 
			+ pow(e.position.y - transform.position.y, 2));

		double time = distance / projectile.speed;

		glm::vec2 direccion;
		direccion.x = (e.position.x - transform.position.x) / time;
		direccion.y = (e.position.y - transform.position.y) / time;
		
		Entity bullet = manager->CreateEntity();
		bullet.AddComponent<CircleColliderComponent>(16.0f);
		bullet.AddComponent<RigidbodyComponent>(glm::vec2(direccion.x, direccion.y), projectile.speed);
		std::cout << direccion.x <<" " << direccion.y << std::endl;
		bullet.AddComponent<SpriteComponent>(projectile.assetId, 16.0f, 16.0f, 0.0f, 0);
		glm::vec2 pos;
		pos.x = transform.position.x;
		pos.y = transform.position.y;
		bullet.AddComponent<TransformComponent>(pos,
			glm::vec2(2, 2), 0);
		bullet.AddComponent<TagComponent>(2);


		auto& transformBullet = bullet.GetComponent<TransformComponent>();
		auto& spriteBullet = bullet.GetComponent<SpriteComponent>();
		glm::vec2 coordsTemp;
		coordsTemp.x = (e.position.x - (transformBullet.position.x + ((sprite.width * transformBullet.scale.x) / 2)));
		coordsTemp.y = (e.position.y - (transformBullet.position.y + ((sprite.height * transformBullet.scale.y) / 2)));

		double angleRadians = atan2(coordsTemp.y, coordsTemp.x);
		double angleDegree = (angleRadians * 180.0 / M_PI);
		angleDegree += 90;  // Rotacion de la imagen

		if (angleDegree < 0) {
			angleDegree = fmod((angleDegree + 360), 360);  // Ajustar el ángulo a un rango de 0 a 360 grados
		}
		transformBullet.rotation = angleDegree;
	}
};
