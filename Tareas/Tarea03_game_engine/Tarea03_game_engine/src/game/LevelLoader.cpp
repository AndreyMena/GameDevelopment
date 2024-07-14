#include "LevelLoader.h"
#include "Game.h"

#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/KeyboardControllerComponent.h"
#include "../Components/MouseControllerComponent.h"
#include "../Components/PlayerDataComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/ScriptComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileComponent.h"

#include <sstream>
#include <string>
#include <../glm/glm.hpp>

LevelLoader::LevelLoader() {
}

LevelLoader::~LevelLoader() {
}

void LevelLoader::LoadLevels(const std::string& game_levels, sol::state& lua) {
	// Verificar que el codigo del script sea correcto
	sol::load_result script = lua.load_file(game_levels);
	if (!script.valid()) {
		sol::error err = script;
		std::string errMessage = err.what();
		std::cout << errMessage << std::endl;
	}

	// Ejecutar el script; lectura de la tabla level
	lua.script_file(game_levels);

	//Lectura de la tabla level
	sol::table levelsLua = lua["levels"];

	int index = 0;
	while (true) {
		// Verificar que exista una entidad
		sol::optional<sol::table> hasLevels = levelsLua[index];
		if (hasLevels == sol::nullopt) {
			break;
		}

		sol::table level_table = levelsLua[index];

		Level level;
		sol::optional<std::string> level_name = level_table["level_name"];
		if (level_name != sol::nullopt) {
			level.level_name = level_table["level_name"];
		}
		sol::optional<std::string> level_path = level_table["level_path"];
		if (level_path != sol::nullopt) {
			level.level_path = level_table["level_path"];
		}
		sol::optional<std::string> terrain_name = level_table["terrain_name"];
		if (terrain_name != sol::nullopt) {
			level.terrain_name = level_table["terrain_name"];
		}
		sol::optional<std::string> terrain_path = level_table["terrain_path"];
		if (terrain_path != sol::nullopt) {
			level.terrain_path = level_table["terrain_path"];
		}
		sol::optional<int> terrain_elements = level_table["terrain_elements"];
		if (terrain_elements != sol::nullopt) {
			level.terrain_elements = level_table["terrain_elements"];
		}
		levels.push_back(level);
		index++;
	}

}

void LevelLoader::LoadLevel(sol::state& lua,
	const std::shared_ptr<ControllerManager>& controllerManager,
	const std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer,
	const std::shared_ptr<AnimationManager>& animationManager,
	const std::shared_ptr<ECSManager>& manager) {

	// Verificar que el codigo del script sea correcto
	sol::load_result script = lua.load_file(levels[actualLevel].level_path);
	if (!script.valid()) {
		sol::error err = script;
		std::string errMessage = err.what();
		std::cout << errMessage << std::endl;
	}
	
	// Ejecutar el script; lectura de la tabla level
	lua.script_file(levels[actualLevel].level_path);

	//Lectura de la tabla level
	sol::table level = lua["level"];

	// Lectura de la subtabla de key-action
	sol::table keyActions = level["keyActions"];
	LoadKeyAction(keyActions, controllerManager);

	// Lectura de la subtabla de key-action
	sol::table backgrounds = level["backgrounds"];
	LoadBackground(backgrounds, controllerManager);

	// Lectura de la subtabla assets
	sol::table assets = level["assets"];
	LoadAssets(assets, assetStore, renderer);

	// Lectura de la subtabla de animaciones
	sol::table animations = level["animations"];
	LoadAnimation(animations, animationManager);

	// Lectura de la subtabla de mapa
	sol::table map = level["map"];
	LoadMap(map, manager);

	// Lectura de la subtabla de entidades
	sol::table entities = level["entities"];
	LoadEntities(entities, lua, manager);
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
	//std::cout << collider.GetTag() << std::endl;
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
					levels[actualLevel].terrain_name,
					tileWidth,
					tileHeight,
					((tileId - 1) % levels[actualLevel].terrain_elements/*11*//*22*/ /*Elementos del terrain*/) * tileWidth,
					((tileId - 1) / levels[actualLevel].terrain_elements/*11*//*22*/) * tileHeight
				);
			}

			tileNumber++;
			tmpNumber.str("");
		}

		pos++;
	}
}

void LevelLoader::LoadKeyAction(const sol::table& keyActions, 
	const std::shared_ptr<ControllerManager>& controllerManager) {
	int index = 0;
	while (true) {
		// Verificacion de que exista un asset
		sol::optional<sol::table> hasKeyAction= keyActions[index];
		if (hasKeyAction == sol::nullopt) {
			break;
		}

		// Obtener el asset
		sol::table keyAction = keyActions[index];

		//Obtener valores del asset
		std::string key = keyAction["key"];
		std::string action = keyAction["action"];
		int macro = keyAction["valueMacro"];

		// Asociar teclas y acciones
		controllerManager->AddKeyAction(macro, action);

		index++;
	}
}

void LevelLoader::LoadBackground(const sol::table& backgrounds,
	const std::shared_ptr<ControllerManager>& controllerManager) {
	int index = 0;
	std::vector<std::string> bg;
	while (true) {
		// Verificacion de que exista un asset
		sol::optional<sol::table> hasbackground = backgrounds[index];
		if (hasbackground == sol::nullopt) {
			break;
		}

		// Obtener el asset
		sol::table background = backgrounds[index];

		//Obtener valores del asset
		std::string asset = background["asset"];

		bg.push_back(asset);

		index++;
	}
	Game::GetInstance().backgroundLevels.push_back(bg);
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

void LevelLoader::LoadAnimation(const sol::table& animations, 
	const std::shared_ptr<AnimationManager>& animationManager) {
	int index = 0;
	while (true) {
		// Verificacion de que exista un asset
		sol::optional<sol::table> hasAnimations= animations[index];
		if (hasAnimations == sol::nullopt) {
			break;
		}

		// Obtener el asset
		sol::table animation = animations[index];

		//Obtener valores del asset
		std::string entityType = animation["entityType"];
		std::string id = animation["id"];
		std::string spriteId = animation["spriteId"];
		int width = animation["w"];
		int height = animation["h"];
		int numFrames = animation["numFrames"];
		int currentFrame = animation["currentFrame"];
		int speedRate = animation["speedRate"];
		bool isLoop = animation["isLoop"];
		int srcRectX = animation["srcRectX"];
		int srcRectY = animation["srcRectY"];

		// Add animation information
		animationManager->AddAnimation(entityType, id, spriteId, width, height, 
			numFrames, currentFrame, speedRate, srcRectX, srcRectY, isLoop);

		index++;
	}
}

void LevelLoader::LoadMap(const sol::table& map, 
	const std::shared_ptr<ECSManager>& manager) {

	std::string mapPath = map["path"];

	// Crear un documento XML  de tinyXML
	tinyxml2::XMLDocument level;
	// Se carga el archivo
	level.LoadFile(mapPath.c_str());

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

void LevelLoader::LoadEntities(const sol::table& entities, sol::state& lua,
	const std::shared_ptr<ECSManager>& manager) {
	int index = 0;
	while (true) {
		// Verificar que exista una entidad
		sol::optional<sol::table> hasEntity = entities[index];
		if (hasEntity == sol::nullopt) {
			break;
		}

		sol::table entity = entities[index];

		Entity newEntity = manager->CreateEntity();

		// Tag
		sol::optional<std::string> tag = entity["tag"];
		if (tag != sol::nullopt) {
			newEntity.AddTag(entity["tag"]);
		}

		// Component
		sol::optional<sol::table> hasComponents = entity["components"];
		if (hasComponents != sol::nullopt) {
			sol::table components = entity["components"];

			// AnimationComponent
			sol::optional<sol::table> animation = components["animation"];
			if (animation != sol::nullopt) {
				newEntity.AddComponent<AnimationComponent>(
					components["animation"]["numFrames"],
					components["animation"]["currentFrame"],
					components["animation"]["frameSpeedRate"],
					components["animation"]["isLoop"],
					true,
					components["animation"]["lifes"]
				);
			}
			//BoxColliderComponent
			sol::optional<sol::table> boxCollider = components["boxCollider"];
			if (boxCollider != sol::nullopt) {
				newEntity.AddComponent<BoxColliderComponent>(
					components["boxCollider"]["w"],
					components["boxCollider"]["h"],
					glm::vec2(
						components["boxCollider"]["offset"]["x"],
						components["boxCollider"]["offset"]["y"]
					)
				);
			}

			// CameraFollowComponent
			sol::optional<sol::table> cameraFollow = components["cameraFollow"];
			if (cameraFollow != sol::nullopt) {
				newEntity.AddComponent<CameraFollowComponent>();
			}

			// RigidbodyComponent
			sol::optional<sol::table> rigidbody = components["rigidbody"];
			if (rigidbody != sol::nullopt) {
				newEntity.AddComponent<RigidbodyComponent>(
					components["rigidbody"]["isStatic"],
					components["rigidbody"]["mass"]
				);
			}

			// ScriptComponent
			sol::optional<sol::table> script = components["script"];
			if (script != sol::nullopt) {
				lua["awake"] = sol::nil;
				lua["update"] = sol::nil;
				lua["on_collision"] = sol::nil;
				std::string scriptPath = components["script"]["path"];
				lua.script_file(scriptPath);

				sol::optional<sol::function> hasAwake= lua["awake"];
				sol::function awake = sol::nil;
				if (hasAwake != sol::nullopt) {
					awake = lua["awake"];
				}

				sol::optional<sol::function> hasUpdate = lua["update"];
				sol::function update = sol::nil;
				if (hasUpdate != sol::nullopt) {
					update = lua["update"];
				}

				sol::optional<sol::function> hasOnCollision= lua["on_collision"];
				sol::function onCollision = sol::nil;
				if (hasOnCollision != sol::nullopt) {
					onCollision = lua["on_collision"];
				}

				newEntity.AddComponent<ScriptComponent>(awake, update, onCollision);
			}

			// SpriteComponent
			sol::optional<sol::table> sprite = components["sprite"];
			if (sprite != sol::nullopt) {
				newEntity.AddComponent<SpriteComponent>(
					components["sprite"]["assetId"], 
					components["sprite"]["w"], 
					components["sprite"]["h"], 
					components["sprite"]["srcRectX"], 
					components["sprite"]["srcRectY"],
					components["sprite"]["spacingRect"],
					components["sprite"]["startRect"],
					components["sprite"]["flip"]
				);
			}

			// TransformComponent
			sol::optional<sol::table> transform = components["sprite"];
			if (transform != sol::nullopt) {
				newEntity.AddComponent<TransformComponent>(
					glm::vec2(
						components["transform"]["position"]["x"],
						components["transform"]["position"]["y"]
					),
					glm::vec2(
						components["transform"]["scale"]["x"],
						components["transform"]["scale"]["y"]
					),
					components["transform"]["rotation"]
				);
			}

			// ProjectileComponent
			sol::optional<sol::table> projectile = components["projectile"];
			if (projectile != sol::nullopt) {
				newEntity.AddComponent<ProjectileComponent>(
					components["projectile"]["assetId"],
					components["projectile"]["speedProjectile"],
					components["projectile"]["mass"],
					components["projectile"]["width"],
					components["projectile"]["height"]
				);
			}
		}

		index++;
	}
}

void LevelLoader::LoadNextLevel(sol::state& lua,
	const std::shared_ptr<ControllerManager>& controllerManager,
	const std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer,
	const std::shared_ptr<AnimationManager>& animationManager,
	const std::shared_ptr<ECSManager>& manager) {
	//Se avanza de nivel
	actualLevel++;

	//Se eliminan todas las entidades del nivel anterior
	manager->KillAllEntities();

	//Se carga el nivel
	LoadLevel(lua, controllerManager, assetStore,
		renderer, animationManager, manager);
}

