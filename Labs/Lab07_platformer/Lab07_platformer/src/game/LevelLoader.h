#pragma once

#include <tinyxml2/tinyxml2.h>
#include <memory>
#include "../ECS/ECS.h"

class LevelLoader {
	void LoadMapSprites(const std::shared_ptr<ECSManager>& manager,
		tinyxml2::XMLElement* layer, int tileWidth, int tileHeight,
		int levelWidth, int levelHeight);
	
	void LoadMapColliders(const std::shared_ptr<ECSManager>& manager,
		tinyxml2::XMLElement* object);
	
public:
	LevelLoader();
	~LevelLoader();

	void LoadMap(const std::shared_ptr<ECSManager>& manager,
		const std::string& levelPath);
};
