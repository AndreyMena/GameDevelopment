#pragma once

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/ProjectileEvent.h"
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/SpriteComponent.h"
#include <memory>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <sol/sol.hpp>

class ProjectileEmitterSystem : public System {
	std::shared_ptr<ECSManager>& manager;
	sol::state& lua;
public:
	ProjectileEmitterSystem(std::shared_ptr<ECSManager>& manager, sol::state& lua) : manager(manager), lua(lua) {
		RequireComponent<ProjectileComponent>();
	}

	void SubscribeToProjectileEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<ProjectileEmitterSystem, ProjectileEvent>(this,
			&ProjectileEmitterSystem::OnProjectileEvent);
	}

	void OnProjectileEvent(ProjectileEvent& e) {
		auto entities = GetSystemEntities();
		auto entity = entities[0];  // Player

		auto& transform = entity.GetComponent<TransformComponent>();
		auto& sprite = entity.GetComponent<SpriteComponent>();
		auto& projectile = entity.GetComponent<ProjectileComponent>();

		double distance = sqrt(pow(e.position.x - transform.position.x, 2)
			+ pow(e.position.y - transform.position.y, 2));

		double time = distance / projectile.speed;

		Entity bullet = manager->CreateEntity();
		bullet.AddComponent<BoxColliderComponent>(projectile.width, projectile.height);
		//bullet.AddComponent<CircleColliderComponent>(24);
		bullet.AddComponent<RigidbodyComponent>(false, projectile.mass);
		auto& bulletRigid = bullet.GetComponent<RigidbodyComponent>();

		double angleDegree = 0;
		glm::vec2 pos;
		pos.y = transform.position.y - 1;
		if (sprite.flip == false) {
			bulletRigid.velocity.x = 600;
			pos.x = transform.position.x + sprite.width;
		}else{
			bulletRigid.velocity.x = -600;
			angleDegree = 180;  // Rotacion de la imagen cambiar a +90 dependiendo de imagen
			pos.x = transform.position.x - sprite.width;
		}
		bulletRigid.velocity.y = 0;

		bullet.AddComponent<SpriteComponent>(projectile.assetId, 
			projectile.width, projectile.height, 0.0f, 0.0f);

		bullet.AddComponent<TransformComponent>(pos,
			glm::vec2(2, 2), 0);

		bullet.AddTag("arrow");

		auto& transformBullet = bullet.GetComponent<TransformComponent>();

		transformBullet.rotation = angleDegree;

		// ScriptComponent
		// Verificar que el codigo del script sea correcto
		lua["awake"] = sol::nil;
		std::string scriptPath = "./assets/scripts/arrow.lua";

		Game::GetInstance().lua.script_file(scriptPath);
		sol::optional<sol::function> hasAwake = Game::GetInstance().lua["awake"];
		sol::function awake = sol::nil;
		if (hasAwake != sol::nullopt) {
			awake = Game::GetInstance().lua["awake"];
		}

		sol::optional<sol::function> hasUpdate = Game::GetInstance().lua["update"];
		sol::function update = sol::nil;
		if (hasUpdate != sol::nullopt) {
			update = Game::GetInstance().lua["update"];
		}

		sol::optional<sol::function> hasOnCollision = Game::GetInstance().lua["on_collision"];
		sol::function onCollision = sol::nil;
		if (hasOnCollision != sol::nullopt) {
			onCollision = Game::GetInstance().lua["on_collision"];
		}

		bullet.AddComponent<ScriptComponent>(awake, update, onCollision);
	}
};
