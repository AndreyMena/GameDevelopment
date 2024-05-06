#pragma once

#include "../ECS/ECS.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"

#include "../EventManager/EventManager.h"
#include "../Events/PlayerDeathEvent.h"
#include <iostream>

class GameStateSystem : public System {
public:
	GameStateSystem() {
		RequireComponent<RigidbodyComponent>();
		RequireComponent<TransformComponent>();
		this->SetPlayer(0);
	}

	void SubscribeToOnPlayerDeathEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<GameStateSystem, PlayerDeathEvent>(this,
			&GameStateSystem::OnPlayerDeathEvent);
	}

	void OnPlayerDeathEvent(PlayerDeathEvent& e) {
		//e.bullet.Kill();
	}

	void Update(std::shared_ptr<EventManager>& eventManager) {
	}
};
