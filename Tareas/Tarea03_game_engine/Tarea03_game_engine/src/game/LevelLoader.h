#pragma once

#include "../AnimationManager/AnimationManager.h"
#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include "../ControllerManager/ControllerManager.h"
#include "../Util/Level.h"

#include <memory>
#include <vector>
#include <SDL.h>
#include <sol/sol.hpp>
#include <tinyxml2/tinyxml2.h>

class LevelLoader {
	void LoadMapSprites(const std::shared_ptr<ECSManager>& manager,
		tinyxml2::XMLElement* layer, int tileWidth, int tileHeight,
		int levelWidth, int levelHeight);
	
	void LoadMapColliders(const std::shared_ptr<ECSManager>& manager,
		tinyxml2::XMLElement* object);
	
	void LoadKeyAction(const sol::table& keyActions, 
		const std::shared_ptr<ControllerManager>& controllerManager);
	void LoadAssets(const sol::table& assets, 
		const std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);

	void LoadAnimation(const sol::table& animations,
		const std::shared_ptr<AnimationManager>& animationManager);

	void LoadMap(const sol::table& map, 
		const std::shared_ptr<ECSManager>& manager);

	void LoadEntities(const sol::table& entities, sol::state& lua,
		const std::shared_ptr<ECSManager>& manager);

	std::vector<Level> levels;
public:
	int actualLevel = 0;
	LevelLoader();
	~LevelLoader();

	void LoadNextLevel(sol::state& lua,
		const std::shared_ptr<ControllerManager>& controllerManager,
		const std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer,
		const std::shared_ptr<AnimationManager>& animationManager,
		const std::shared_ptr<ECSManager>& manager);

	void LoadLevel(sol::state& lua,
		const std::shared_ptr<ControllerManager>& controllerManager,
		const std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer, 
		const std::shared_ptr<AnimationManager>& animationManager,
		const std::shared_ptr<ECSManager>& manager);
	
	void LoadLevels(const std::string& levels, sol::state& lua);
};
