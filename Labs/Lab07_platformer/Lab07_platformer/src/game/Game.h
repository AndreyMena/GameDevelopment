#pragma once
#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"

#include <SDL.h>
#include <memory>
#include <string>
#include <tinyxml2/tinyxml2.h>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS; //16.6

class Game {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	size_t windowWidth = 0;
	size_t windowHeight = 0;

	bool isRunning = false;

	int mPrvsFrame = 0; //miliseconds previous frame

	std::shared_ptr<AssetStore> assetStore;
	std::shared_ptr<ECSManager> manager;
	std::shared_ptr<EventManager> eventManager;

	void CreateLevel(tinyxml2::XMLElement* layer, int tileWidth, int tileHeight,
		int levelWidth, int levelHeight);
	void LoadLevelMap(const std::string& levelPath);

	void Setup();
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

