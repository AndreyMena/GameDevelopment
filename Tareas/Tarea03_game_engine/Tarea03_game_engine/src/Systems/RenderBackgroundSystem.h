#pragma once

#include "../ECS/ECS.h"
#include "../Components/BackGroundComponent.h"
#include "../AssetStore/AssetStore.h"
#include <SDL.h>

class RenderBackgroundSystem : public System {
public:
	RenderBackgroundSystem() {
		RequireComponent<BackGroundComponent>();
	}

	void Update(SDL_Renderer* renderer, std::shared_ptr<AssetStore>& assetStore,
		size_t windowWidth, size_t windowHeight) {
		for (auto entity : GetSystemEntities()) {
			const auto& background= entity.GetComponent<BackGroundComponent>();

			//Background
			SDL_Rect destination;
			destination.x = 0;
			destination.y = 0;
			destination.w = windowWidth;
			destination.h = windowHeight;
			SDL_RenderCopy(renderer, assetStore->GetTexture(background.asset), NULL, &destination);
		}
	}
};