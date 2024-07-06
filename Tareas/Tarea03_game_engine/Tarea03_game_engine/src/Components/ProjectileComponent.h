#pragma once

#include <string>

struct ProjectileComponent {
	std::string assetId;
	int speed;
	float mass;
	int width;
	int height;

	ProjectileComponent(std::string assetId = "", int speed = 0, float mass = 0.0, 
		int width = 0, int height = 0) {
		this->assetId = assetId;
		this->speed = speed;
		this->mass = mass;
		this->width = width;
		this->height = height;
	}
};