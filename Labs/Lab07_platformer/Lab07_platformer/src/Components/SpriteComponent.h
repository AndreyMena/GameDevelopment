#pragma once

#include <string>
#include <SDL.h>

struct SpriteComponent {
	std::string assetId;
	int width;
	int height;
	SDL_Rect srcRect;
	bool flip = false;

	SpriteComponent(const std::string& assetId = "", int width = 0, 
		int height = 0, int srcRectX = 0, int srcRectY = 0) {
		this->assetId = assetId;
		this->width = width;
		this->height = height;
		srcRect = { srcRectX, srcRectY, width, height };
	}
};