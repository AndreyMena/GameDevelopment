#pragma once

#include "../Util/Image.h"
#include <string>

struct RespawnComponent {
	Image image;
	int speed;
	glm::vec2 position;
	float scale;
	std::string assetBullet;
	int speedBullet;

	RespawnComponent(Image image = Image(), int speed = 0,
		glm::vec2 position = glm::vec2(0, 0), float scale = 1.0, 
		std::string assetBullet = "", int speedBullet = 0) {
		this->image = image;
		this->speed = speed;
		this->position = position;
		this->scale = scale;
		this->assetBullet = assetBullet;
		this->speedBullet = speedBullet;
	}
};