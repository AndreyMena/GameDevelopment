#pragma once

#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include <memory>

class RenderSystem : public System{
public:
	RenderSystem() {
		RequireComponent<SpriteComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(SDL_Renderer* renderer, std::shared_ptr<AssetStore>& assetStore) {
		for (auto entity : GetSystemEntities()) {
			const auto& sprite = entity.GetComponent<SpriteComponent>();
			const auto& transform = entity.GetComponent<TransformComponent>();
			
			SDL_Rect dstRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				static_cast<int>(sprite.width * transform.scale.x),
				static_cast<int>(sprite.height * transform.scale.y),
			};

			SDL_RenderCopyEx(
				renderer,
				assetStore->GetTexture(sprite.assetId),
				&sprite.srcRect,
				&dstRect,
				transform.rotation,
				NULL,
				SDL_FLIP_NONE
			);
		}
	}
};
