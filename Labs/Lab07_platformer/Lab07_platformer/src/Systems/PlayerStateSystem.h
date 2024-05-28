#pragma once

#include "../AnimationManager/AnimationManager.h"
#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/PlayerDataComponent.h"
#include "../EventManager/EventManager.h"
#include "../ECS/ECS.h"

#include <memory>

class PlayerStateSystem : public System {
public:
	PlayerStateSystem() {
		RequireComponent<SpriteComponent>();
		RequireComponent<PlayerDataComponent>();
		RequireComponent<AnimationComponent>();
		//RequireComponent<RigidbodyComponent>();
	}

	void Update(const std::shared_ptr<AnimationManager>& animationManager) {
		if (GetSystemEntities().size() == 0) {
			return;
		}

		auto player = GetSystemEntities()[0];

		auto& animation = player.GetComponent<AnimationComponent>();
		auto& data = player.GetComponent<PlayerDataComponent>();
		const auto& rigidbody = player.GetComponent<RigidbodyComponent>();
		auto& sprite = player.GetComponent<SpriteComponent>();

		AnimationData animationData;
		bool animationStateHasChanged = false;

		if (rigidbody.velocity.x >= 0.01f) {
			sprite.flip = false;
			if (data.state != PlayerState::run) {
				animationData = animationManager->GetAnimationData("player", "run");
				animationStateHasChanged = true;
				data.state = PlayerState::run;
			}
		}

		if (rigidbody.velocity.x <= -0.01f) {
			sprite.flip = true;
			if (data.state != PlayerState::run) {
				animationData = animationManager->GetAnimationData("player", "run");
				animationStateHasChanged = true;
				data.state = PlayerState::run;
			}
		}
		if (rigidbody.velocity.x <= -0.01f) {
			if (data.state != PlayerState::jump) {
				animationData = animationManager->GetAnimationData("player", "jump");
				animationStateHasChanged = true;
				data.state = PlayerState::jump;
			}
		}
		if (rigidbody.velocity.x >= 0.01f) {
			if (data.state != PlayerState::fall) {
				animationData = animationManager->GetAnimationData("player", "fall");
				animationStateHasChanged = true;
				data.state = PlayerState::fall;
			}
		}
		if (rigidbody.velocity.x < 0.01f && -0.01f < rigidbody.velocity.x
			&& rigidbody.velocity.y < 0.01f && -0.01f < rigidbody.velocity.y) {
			if (data.state != PlayerState::idle) {
				animationData = animationManager->GetAnimationData("player", "idle");
				animationStateHasChanged = true;
				data.state = PlayerState::idle;
			}
		}

		if (animationStateHasChanged) {
			sprite.assetId = animationData.spriteLabel;
			sprite.width = animationData.widht;
			sprite.height = animationData.height;
			sprite.srcRect.x = 0;
			sprite.srcRect.y = 0;

			animation.currentFrame = animation.currentFrame;
			animation.frameSpeedRate = animation.frameSpeedRate;
			animation.numberOffFrames = animation.numberOffFrames;
			animation.isLoop = animation.isLoop;
			animation.startTime = SDL_GetTicks();
		}
	}
};