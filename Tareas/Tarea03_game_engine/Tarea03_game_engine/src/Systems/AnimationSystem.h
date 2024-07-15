#pragma once

#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"
#include "../EventManager/EventManager.h"
#include "../ECS/ECS.h"

class AnimationSystem : public System {
public:
	AnimationSystem() {
		RequireComponent<AnimationComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update() {
		for (auto entity : GetSystemEntities()) {
			auto& animation = entity.GetComponent<AnimationComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();

			if (entity.GetTag() == "boss" && animation.isAttacking) {
				sprite.width = 240;
				sprite.height = 192;
				sprite.srcRect.w = 240;
				sprite.srcRect.h = 192;
			} else if (entity.GetTag() == "boss" && !animation.isAttacking) {
				sprite.width = 160;
				sprite.height = 144;
				sprite.srcRect.w = 160;
				sprite.srcRect.h = 144;
			}
			animation.currentFrame = ((SDL_GetTicks() - animation.startTime)
				* animation.frameSpeedRate / 1000) % animation.numberOffFrames;

			sprite.srcRect.x = sprite.startRect + (animation.currentFrame * (sprite.width + sprite.spacingRect));
		}
	}
};
