#pragma once

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include <SDL.h>

class RenderBoxColliderSystem : System {
	RenderBoxColliderSystem() {
		RequireComponent<BoxColliderComponent>();
		RequireComponent<TransformComponent>();
	}
	~RenderBoxColliderSystem();

	void Update(SDL_Renderer* renderer) {
		for (auto entity : GetSystemEntities()) {
			const auto& collider = entity.GetComponent<BoxColliderComponent>();
			const auto& transform = entity.GetComponent<TransformComponent>();

			SDL_Rect box = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				static_cast<int>(collider.width * transform.scale.x),
				static_cast<int>(collider.height * transform.scale.y)
			};

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(renderer, &box);

		}
	}
};