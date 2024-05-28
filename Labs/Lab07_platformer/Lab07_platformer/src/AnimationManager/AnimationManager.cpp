#include "AnimationManager.h"

AnimationManager::AnimationManager() {
}

AnimationManager::~AnimationManager() {
}

void AnimationManager::AddAnimation(const std::string& entityType, 
	const std::string& label, const std::string& spriteLabel, int widht, 
	int height, int numberFrames, int currentFrame, int frameSpeedRate, 
	bool isLoop) {

	auto animationData = AnimationData(
		spriteLabel,
		widht,
		height,
		numberFrames,
		currentFrame,
		frameSpeedRate,
		isLoop
	);

	animations[entityType][label] = animationData;
}

AnimationData AnimationManager::GetAnimationData(const std::string& entityType, 
	const std::string& label) {
	return animations[entityType][label];
}
