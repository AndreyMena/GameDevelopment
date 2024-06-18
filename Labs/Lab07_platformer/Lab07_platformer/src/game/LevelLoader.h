#pragma once

#include "../AnimationManager/AnimationManager.h"
#include "../KeyActionMap/KeyActionMap.h"
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"

#include <memory>
#include <SDL.h>
#include <tinyxml2/tinyxml2.h>

class LevelLoader {
	void LoadMapSprites(const std::shared_ptr<ECSManager>& manager,
		tinyxml2::XMLElement* layer, int tileWidth, int tileHeight,
		int levelWidth, int levelHeight);
	
	void LoadMapColliders(const std::shared_ptr<ECSManager>& manager,
		tinyxml2::XMLElement* object);
	
	void LoadKeyAction(const std::shared_ptr<KeyActionMap>& keyActionMap);
	void LoadAssets(const std::shared_ptr<AssetStore>& assetStore, 
		SDL_Renderer* renderer);

	void LoadAnimation(const std::shared_ptr<AnimationManager>& animationManager);

	void LoadMap(const std::shared_ptr<ECSManager>& manager,
		const std::string& levelPath);

public:
	LevelLoader();
	~LevelLoader();

	void LoadLevel(const std::shared_ptr<KeyActionMap>& keyActionMap, 
		const std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer, 
		const std::shared_ptr<AnimationManager>& animationManager,
		const std::shared_ptr<ECSManager>& manager, const std::string& levelName);

};