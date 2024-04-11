#pragma once
#include <string>
#include <glm/glm.hpp>

struct Entity
{
	std::string name;
	std::string directory;
	size_t imgWidth;
	size_t imgHeight;
	glm::vec2 pos = glm::vec2();
	glm::vec2 imgVel = glm::vec2();
	int xPos;
	int yPos;
	int xVel;
	int yVel;
	double angle;
};
