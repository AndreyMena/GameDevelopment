#pragma once

#include <iostream>

struct EnemyGeneratorComponent {
	std::string assetId;
	int score;
	int minSpeed;
	int maxSpeed;
	int spawnRate;

	EnemyGeneratorComponent(std::string assetId, int score = 0, 
		int minSpeed = 0, int maxSpeed = 0, int spawnRate = 0) {
		this->assetId = assetId;
		this->score = score;
		this->minSpeed = minSpeed;
		this->maxSpeed = maxSpeed;
		this->spawnRate = spawnRate;
	}
};
