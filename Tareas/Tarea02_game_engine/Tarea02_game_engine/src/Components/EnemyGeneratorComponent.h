#pragma once

#include <iostream>
#include "../Util/Image.h"

struct EnemyGeneratorComponent {
	std::string assetId;
	int score;
	int minSpeed;
	int maxSpeed;
	double spawnRate;
	double timeSinceLastSpawn;
	Image image;

	EnemyGeneratorComponent(std::string assetId = "", Image image = Image(), int score = 0,
		int minSpeed = 0, int maxSpeed = 0, int spawnRate = 0, double timeSinceLastSpawn = 0.0) {
		this->assetId = assetId;
		this->score = score;
		this->minSpeed = minSpeed;
		this->maxSpeed = maxSpeed;
		this->spawnRate = spawnRate;
		this->timeSinceLastSpawn = timeSinceLastSpawn;
		this->image = image;
	}
};
