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

void LevelLoader::LoadLevel(const std::string& levelName, sol::state& lua,
	const std::shared_ptr<KeyActionMap>& keyActionMap,
	const std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer,
	const std::shared_ptr<AnimationManager>& animationManager,
	const std::shared_ptr<ECSManager>& manager, const std::string& mapPath) {

	// Verificar que el codigo del script sea correcto
	sol::load_result script = lua.load_file("./assets/scripts/"+ levelName);
	if (!script.valid()) {
		sol::error err = script;
		std::string errMessage = err.what();
		std::cout << errMessage << std::endl;
	}
	
	// Ejecutar el script; lectura de la tabla level
	lua.script_file("./assets/scripts/" + levelName);

	//Lectura de la tabla level
	sol::table level = lua["level"];

	// Asociar teclas y acciones
	LoadKeyAction(keyActionMap);

	// Lectura de la subtabla assets
	sol::table assets = level["assets"];
	LoadAssets(assets, assetStore, renderer);

	// Add animation info5rmation
	LoadAnimation(animationManager);

	// Load Map
	LoadMap(manager, "./assets/levels/level_02.tmx");
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

void LevelLoader::LoadKeyAction(const std::shared_ptr<KeyActionMap>& keyActionMap) {
	// Asociar teclas y acciones
	keyActionMap->InsertKeyAction(SDLK_UP, "jump");
	keyActionMap->InsertKeyAction(SDLK_RIGHT, "move_right");
	keyActionMap->InsertKeyAction(SDLK_LEFT, "move_left");
}

void LevelLoader::LoadAssets(const sol::table& assets, 
	const std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer) {
	// Cargar Texturas

	int index = 0;
	while (true) {
		// Verificacion de que exista un asset
		sol::optional<sol::table> hasAsset = assets[index];
		if (hasAsset == sol::nullopt) {
			break;
		}

		// Obtener el asset
		sol::table asset = assets[index];

		//Obtener valores del asset
		std::string type = asset["type"];
		std::string id = asset["id"];
		std::string path = asset["path"];

		if (type == "texture") {
			assetStore->AddTexture(id, path, renderer);
		}

		index++;
	}
	// assetStore->AddTexture("terrain_img", "./assets/img/terrain.png", renderer);
}

void LevelLoader::LoadAnimation(const std::shared_ptr<AnimationManager>& animationManager) {
	// Add animation info5rmation
	animationManager->AddAnimation("player", "idle", "frog_idle", 32, 32, 11
		, 1, 15, true);
	animationManager->AddAnimation("player", "run", "frog_run", 32, 32, 12
		, 1, 15, true);
	animationManager->AddAnimation("player", "fall", "frog_fall", 32, 32, 1
		, 1, 1, true);
	animationManager->AddAnimation("player", "jump", "frog_jump", 32, 32, 1
		, 1, 1, true);
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

