#pragma once

#include "../AnimationManager/AnimationManager.h"
#include "../KeyActionMap/KeyActionMap.h"
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"

#include <memory>
#include <SDL.h>
#include <sol/sol.hpp>
#include <tinyxml2/tinyxml2.h>

class LevelLoader {
	void LoadMapSprites(const std::shared_ptr<ECSManager>& manager,
		tinyxml2::XMLElement* layer, int tileWidth, int tileHeight,
		int levelWidth, int levelHeight);
	
	void LoadMapColliders(const std::shared_ptr<ECSManager>& manager,
		tinyxml2::XMLElement* object);
	
	void LoadKeyAction(const sol::table& keyActions, const std::shared_ptr<KeyActionMap>& keyActionMap);
	void LoadAssets(const sol::table& assets, 
		const std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);

	void LoadAnimation(const sol::table& animations,
		const std::shared_ptr<AnimationManager>& animationManager);

	void LoadMap(const sol::table& map, 
		const std::shared_ptr<ECSManager>& manager);

	void LoadEntities(const sol::table& entities,
		const std::shared_ptr<ECSManager>& manager);
public:
	LevelLoader();
	~LevelLoader();

	void LoadLevel(const std::string& levelName, sol::state& lua,
		const std::shared_ptr<KeyActionMap>& keyActionMap, 
		const std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer, 
		const std::shared_ptr<AnimationManager>& animationManager,
		const std::shared_ptr<ECSManager>& manager);

};
