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
		if (sprite.flip == false) {
			bulletRigid.velocity.x = 600;
		}else{
			bulletRigid.velocity.x = -600;
			angleDegree = 180;  // Rotacion de la imagen cambiar a +90 dependiendo de imagen
		}
		bulletRigid.velocity.y = 0;
		//bulletRigid.mass = projectile.mass;

		bullet.AddComponent<SpriteComponent>(projectile.assetId, 
			projectile.width, projectile.height, 0.0f, 0, 0);
		glm::vec2 pos;
		pos.x = transform.position.x;
		pos.y = transform.position.y;
		bullet.AddComponent<TransformComponent>(pos,
			glm::vec2(2, 2), 0);
		bullet.AddTag("arrow");

		auto& transformBullet = bullet.GetComponent<TransformComponent>();

		transformBullet.rotation = angleDegree;

		// ScriptComponent
		/*
		lua["awake"] = sol::nil;
		lua["update"] = sol::nil;
		lua["on_collision"] = sol::nil;
		std::string scriptPath = "./assets/scripts/arrow.lua";
		lua.script_file(scriptPath);

		sol::optional<sol::function> hasAwake = lua["awake"];
		sol::function awake = sol::nil;
		if (hasAwake != sol::nullopt) {
			awake = lua["awake"];
		}

		sol::optional<sol::function> hasUpdate = lua["update"];
		sol::function update = sol::nil;
		if (hasUpdate != sol::nullopt) {
			update = lua["update"];
		}

		sol::optional<sol::function> hasOnCollision = lua["on_collision"];
		sol::function onCollision = sol::nil;
		if (hasOnCollision != sol::nullopt) {
			onCollision = lua["on_collision"];
		}

		bullet.AddComponent<ScriptComponent>(awake, update, onCollision);
		*/
	}
};
