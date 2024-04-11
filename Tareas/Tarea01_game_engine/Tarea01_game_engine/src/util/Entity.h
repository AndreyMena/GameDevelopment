#pragma once
#include <string>
#include <glm/glm.hpp>
#include <SDL.h>

struct Entity
{
	std::string name;
	std::string directory;
	size_t imgWidth;
	size_t imgHeight;
	glm::vec2 pos = glm::vec2();
	glm::vec2 imgVel = glm::vec2();
	double angle;
	SDL_Rect srcRect = { 0, 0, 0, 0 };
	SDL_Surface* imgSurface = nullptr;
	SDL_Texture* imgTexture = nullptr;
	SDL_Rect imgDstRect = { 0, 0, 0, 0 };
};
