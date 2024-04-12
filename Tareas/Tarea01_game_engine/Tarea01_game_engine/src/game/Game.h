#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "../util/Color.h"
#include "../util/Font.h"
#include "../util/Entity.h"
#include <vector>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS; //16.6

class Game {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	size_t windowWidth = 0;
	size_t windowHeight = 0;
	Color windowColor;

	Font font;
	TTF_Font* ttfFont = nullptr;
	SDL_Color fontColor = { 0, 0, 0 };

	bool isRunning = false;
	int mPrvsFrame = 0; //miliseconds previous frame

	std::vector<Entity> entitiesVector;

	// Atributos del texto
	SDL_Texture* txtTexture = nullptr;
	std::string message = "";
	glm::vec2 txtPos = glm::vec2();
	size_t txtWidth = 0;
	size_t txtHeight = 0;
	double txtAngle = 0.0;

	void processInput();
	void update();
	void render();
public:
	Game();
	~Game();
	void init();
	void run();
	void destroy();
};


#endif // !GAME_H


