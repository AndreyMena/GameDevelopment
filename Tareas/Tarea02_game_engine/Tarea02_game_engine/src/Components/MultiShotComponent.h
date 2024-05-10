#pragma once
#include <string>

struct MultiShotComponent {
	std::string assetId;
	//Milliseconds
	double timeSinceLastUse;
	double timeLimitPerUse;

	MultiShotComponent(std::string assetId = "", double timeSinceLastUse = 0.0,
		double timeLimitPerUse = 0.0) {
		this->timeSinceLastUse = timeSinceLastUse;
		this->timeLimitPerUse = timeLimitPerUse;
		this->assetId = assetId;
	}
};