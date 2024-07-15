#pragma once

#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../EventManager/EventManager.h"
#include "../ECS/ECS.h"

class AnimationSystem : public System {
	bool checkAnimation = false;
public:
	AnimationSystem() {
		RequireComponent<AnimationComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update() {
		for (auto entity : GetSystemEntities()) {
			auto& animation = entity.GetComponent<AnimationComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();

			if (entity.GetTag() == "boss" && animation.isAttacking) {
				sprite.width = 240;
				sprite.height = 192;
				sprite.srcRect.w = 240;
				sprite.srcRect.h = 192;
				if (!checkAnimation) {
					checkAnimation = true;
					glm::vec2 velocity = glm::vec2(64, 0);
					rigidbody.velocity = velocity;
				}
			} else if (entity.GetTag() == "boss" && !animation.isAttacking) {
				sprite.width = 160;
				sprite.height = 144;
				sprite.srcRect.w = 160;
				sprite.srcRect.h = 144;
				checkAnimation = false;
			}
			animation.currentFrame = ((SDL_GetTicks() - animation.startTime)
				* animation.frameSpeedRate / 1000) % animation.numberOffFrames;

			sprite.srcRect.x = sprite.startRect + (animation.currentFrame * (sprite.width + sprite.spacingRect));
		}
	}
};
