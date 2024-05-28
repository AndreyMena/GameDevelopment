#pragma once


#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"
#include "../EventManager/EventManager.h"
#include "../ECS/ECS.h"

#include "../Events/CollisionEvent.h"
#include <glm/glm.hpp>
#include <memory>
#include <iostream>


class AnimationSystem : public System {
public:
	AnimationSystem() {
		RequireComponent<AnimationComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update() {
		for (auto entity : GetSystemEntities()) {
			auto& animation = entity.GetComponent<AnimationComponent>();
			auto& sprite= entity.GetComponent<SpriteComponent>();

			animation.currentFrame = ((SDL_GetTicks() - animation.startTime)
				* animation.frameSpeedRate / 1000) % animation.numberOffFrames;

			sprite.srcRect.x = animation.currentFrame * sprite.width;
		}
	}
};
