#pragma once

#include <string>

struct ProjectileEmitterComponent {
	std::string assetId;
	int speed;

	ProjectileEmitterComponent(std::string assetId = "", int speed = 0) {
		this->assetId = assetId;
		this->speed = speed;
	}
};