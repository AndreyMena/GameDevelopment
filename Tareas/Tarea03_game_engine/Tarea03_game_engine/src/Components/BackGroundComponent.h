#pragma once

#include <string>

struct BackGroundComponent {
	std::string asset;

	BackGroundComponent(std::string asset = "") {
		this->asset = asset;
	}
};