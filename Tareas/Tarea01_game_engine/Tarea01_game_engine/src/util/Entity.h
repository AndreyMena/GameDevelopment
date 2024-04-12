#pragma once
#include <string>
#include <glm/glm.hpp>
#include <SDL.h>

struct Entity
{
	//Image attributes
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

	//Text attributes
	SDL_Texture* txtTexture = nullptr;
	std::string message = "";
	glm::vec2 txtPos = glm::vec2();
	size_t txtWidth = 0;
	size_t txtHeight = 0;
	double txtAngle = 0.0;
	SDL_Rect txtDstRect = { 0, 0, 0, 0 };
};
