#pragma once

#include "./LevelLoader.h"

#include "../AnimationManager/AnimationManager.h"
#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../KeyActionMap/KeyActionMap.h"

#include <SDL.h>
#include <memory>
#include <string>
#include <tinyxml2/tinyxml2.h>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS; //16.6

class Game {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera = {0, 0, 0, 0};

	bool isRunning = false;
	bool debugMode = false;

	int mPrvsFrame = 0; //miliseconds previous frame

	std::shared_ptr<AnimationManager> animationManager;
	std::shared_ptr<AssetStore> assetStore;
	std::shared_ptr<ECSManager> manager;
	std::shared_ptr<EventManager> eventManager;
	std::shared_ptr<KeyActionMap> keyActionMap;

	std::shared_ptr<LevelLoader> levelLoader;

	void CreateLevel(tinyxml2::XMLElement* layer, int tileWidth, int tileHeight,
		int levelWidth, int levelHeight);
	void LoadLevelMap(const std::string& levelPath);

	void Setup();
	void processInput();
	void update();
	void render();

public:
	static size_t windowWidth;
	static size_t windowHeight;
	static size_t mapWidth;
	static size_t mapHeight;

	Game();
	~Game();
	void init();
	void run();
	void destroy();
};

