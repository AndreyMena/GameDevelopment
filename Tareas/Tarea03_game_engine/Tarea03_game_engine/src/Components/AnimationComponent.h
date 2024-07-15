#pragma once

#include <SDL.h>

struct AnimationComponent {
	int numberOffFrames;
	int currentFrame;
	int frameSpeedRate;
	bool isLoop;
	int startTime;
	bool animationEnd;
	int lifes;
	bool isAttacking = false;

	AnimationComponent(int numberFrames = 1, int currentFrame = 1,
		int frameSpeedRate = 1, bool isLoop = true, bool animationEnd = true, 
		int lifes = 1) {
		this->numberOffFrames = numberFrames;
		this->currentFrame = currentFrame;
		this->frameSpeedRate = frameSpeedRate;
		this->isLoop = isLoop;
		this->startTime = SDL_GetTicks();
		this->animationEnd = animationEnd;
		this->lifes = lifes;
	}
};