#include "LevelLoader.h"
#include "Game.h"

#include "../Components/AnimationComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/MouseControllerComponent.h"
#include "../Components/KeyboardControllerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/PlayerDataComponent.h"
#include "../Components/CameraFollowComponent.h"

#include <sstream>
#include <../glm/glm.hpp>

LevelLoader::LevelLoader() {
}

LevelLoader::~LevelLoader() {
}

void LevelLoader::LoadMapColliders(const std::shared_ptr<ECSManager>& manager, 
	tinyxml2::XMLElement* object) {
	const char* type;
	std::string tag;
	int x, y, w, h;
	object->QueryStringAttribute("type", &type);
	tag = type;
	object->QueryIntAttribute("x", &x);
	object->QueryIntAttribute("y", &y);
	object->QueryIntAttribute("width", &w);
	object->QueryIntAttribute("height", &h);

	// Se crean las entidades
	Entity collider = manager->CreateEntity();
	collider.AddTag(tag);
	collider.AddComponent<TransformComponent>(glm::vec2(x, y));
	collider.AddComponent<BoxColliderComponent>(w, h);
}


void LevelLoader::LoadMapSprites(const std::shared_ptr<ECSManager>& manager,
	tinyxml2::XMLElement* layer, int tileWidth, int tileHeight,
	int levelWidth, int levelHeight) {
	tinyxml2::XMLElement* layerData = layer->FirstChildElement("data");

	const char* data = layerData->GetText();

	std::stringstream tmpNumber;
	int pos = 0;
	int tileNumber = 0;
	while (true) {
		if (data[pos] == '\0') {
			break;
		}

		if (isdigit(data[pos])) {
			tmpNumber << data[pos];
		}
		else if (!isdigit(data[pos]) && tmpNumber.str().length() != 0) {
			int tileId = std::stoi(tmpNumber.str());

			if (tileId > 0) {
				Entity tile = manager->CreateEntity();
				tile.AddComponent<TransformComponent>(
					glm::vec2(
						(tileNumber % levelWidth) * tileWidth,
						(tileNumber / levelWidth) * tileHeight
					)
				);
				tile.AddComponent<SpriteComponent>(
					"terrain_img",
					tileWidth,
					tileHeight,
					((tileId - 1) % 22) * tileWidth,
					((tileId - 1) / 22) * tileHeight
				);
			}

			tileNumber++;
			tmpNumber.str("");
		}

		pos++;
	}
}

void LevelLoader::LoadMap(const std::shared_ptr<ECSManager>& manager, 
	const std::string& levelPath) {
	// Crear un documento XML  de tinyXML
	tinyxml2::XMLDocument level;
	// Se carga el archivo
	level.LoadFile(levelPath.c_str());

	tinyxml2::XMLElement* root = level.RootElement();
	int tileWidth, tileHeight, levelWidth, levelHeight;
	// Extraer atributos de la raiz
	root->QueryIntAttribute("tilewidth", &tileWidth);
	root->QueryIntAttribute("tileheight", &tileHeight);
	root->QueryIntAttribute("width", &levelWidth);
	root->QueryIntAttribute("height", &levelHeight);

	// Inicializar vairables estaticas
	Game::mapWidth = tileWidth * levelWidth;
	Game::mapHeight = tileHeight * levelHeight;

	tinyxml2::XMLElement* layer = root->FirstChildElement("layer");
	while (layer != nullptr) {
		LoadMapSprites(manager, layer, tileWidth, tileHeight, levelWidth, levelHeight);
		layer = layer->NextSiblingElement("layer");
	}

	// Creacion de BoxColliders
	tinyxml2::XMLElement* objectGroup = root->FirstChildElement("objectgroup");
	tinyxml2::XMLElement* object = objectGroup->FirstChildElement("object");

	while (object != nullptr) {
		LoadMapColliders(manager, object);
		object = object->NextSiblingElement();
	}
}