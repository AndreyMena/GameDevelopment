#pragma once

#include <map>
#include <string>

struct AnimationData{
	std::string spriteLabel;
	int widht;
	int height;
	int numberFrames;
	int currentFrame;
	int frameSpeedRate;
	bool isLoop;
	int srcRectX;
	int srcRectY;
	
	AnimationData(
		const std::string& spriteLabel = "",
		int widht = 0,
		int height = 0,
		int numberFrames = 1,
		int currentFrame = 1,
		int frameSpeedRate = 1,
		bool isLoop = true,
		int srcRectX = 0,
		int srcRectY = 0
	) {
		this->spriteLabel = spriteLabel;
		this->widht = widht;
		this->height = height;
		this->numberFrames = numberFrames;
		this->currentFrame = currentFrame;
		this->frameSpeedRate = frameSpeedRate;
		this->isLoop = isLoop;
		this->srcRectX = srcRectX;
		this->srcRectY = srcRectY;
	}

};

typedef std::map<std::string, AnimationData> AnimationContainer;

class AnimationManager {
	std::map<std::string, AnimationContainer> animations;
public:
	AnimationManager();
	~AnimationManager();

	void AddAnimation(
		const std::string& entityType,
		const std::string& label,
		const std::string& spriteLabel,
		int widht,
		int height,
		int numberFrames,
		int currentFrame,
		int frameSpeedRate,
		int srcRectX,
		int srcRectY,
		bool isLoop = true
	);

	AnimationData GetAnimationData(const std::string& entityType,
		const std::string& label);
};

