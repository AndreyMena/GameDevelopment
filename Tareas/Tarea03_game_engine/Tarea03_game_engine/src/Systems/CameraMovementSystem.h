#pragma once

#include "../AssetStore/AssetStore.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"

#include <SDL.h>

class CameraMovementSystem : public System {
public:
	CameraMovementSystem() {
		RequireComponent<CameraFollowComponent>();
		RequireComponent<TransformComponent>();
	}
	
	void Update(SDL_Rect& camera) {
		for (auto entity : GetSystemEntities()) {
			const auto& transform = entity.GetComponent<TransformComponent>();


			if (transform.position.x + (Game::windowWidth / 2) < Game::mapWidth) {
				camera.x = static_cast<int>(transform.position.x - (Game::windowWidth / 2));
			}
			if (transform.position.y + (Game::windowHeight/ 2) < Game::mapHeight) {
				camera.y = static_cast<int>(transform.position.y - (Game::windowHeight / 2));
			}

			camera.x = camera.x < 0 ? 0 : camera.x;
			camera.y = camera.y < 0 ? 0 : camera.y;
		}
	}
};