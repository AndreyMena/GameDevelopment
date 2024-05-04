#pragma once
#include <SDL.h>
#include <string>

struct Image {
	std::string textureId;
	SDL_Texture* texture;
	int width;
	int height;
};