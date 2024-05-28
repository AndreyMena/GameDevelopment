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

#include "../Events/KeyboardEvent.h"
#include "../Events/MouseMotionEvent.h"

#include "../Systems/CircularCollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardControllerSystem.h"
#include "../Systems/MouseControllerSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/RenderBoxColliderSystem.h"
#include "../Systems/WeightForceSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/OverlapSystem.h"
#include "../Systems/PlayerActionSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/PlayerStateSystem.h"

#include <cstdio>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

Game::Game() {
	animationManager = std::make_shared<AnimationManager>();
	assetStore = std::make_shared<AssetStore>();
	manager = std::make_shared<ECSManager>();
	eventManager = std::make_shared<EventManager>();
	keyActionMap = std::make_shared<KeyActionMap>();
	std::cout << "Se ejecuta el constructor de GAME" << std::endl;
}

Game::~Game() {
	std::cout << "Se ejecuta el destructor de GAME" << std::endl;
}

void Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error al inicializar SDL" << std::endl;
		return;
	}

	windowWidth = 30 * 16;  // 800
	windowHeight = 20 * 16;  // 600

	this->window = SDL_CreateWindow(
		"Lab 05: Motor de videojuegos",
		//SDL_WINDOWPOS_CENTERED, 
		//SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_UNDEFINED_DISPLAY(1),
		SDL_WINDOWPOS_UNDEFINED_DISPLAY(1),
		this->windowWidth,
		this->windowHeight, 
		SDL_WINDOW_SHOWN);
	// TODO: Verificar que se crea la ventana

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	// TODO: Verificar que se crea el renderer
	
	isRunning = true;
}

void Game::CreateLevel(tinyxml2::XMLElement* layer, int tileWidth, int tileHeight, 
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
		}else if (!isdigit(data[pos]) && tmpNumber.str().length() != 0) {
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
					((tileId -1) % 22) * tileWidth,
					((tileId -1) / 22) * tileHeight
				);
			}

			tileNumber++;
			tmpNumber.str("");
		}

		pos++;
	}
}

void Game::LoadLevelMap(const std::string& levelPath) {
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

	tinyxml2::XMLElement* layer = root->FirstChildElement("layer");
	while (layer != nullptr) {
		CreateLevel(layer, tileWidth, tileHeight, levelWidth, levelHeight);
		layer = layer->NextSiblingElement("layer");
	}

	// TODO Modularizar mas adelante
	// Creacion de BoxColliders
	tinyxml2::XMLElement* objectGroup = root->FirstChildElement("objectgroup");
	tinyxml2::XMLElement* object = objectGroup->FirstChildElement("object");

	while (object != nullptr) {
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

		object = object->NextSiblingElement();
	}
}

void Game::Setup() {
	// Asociar teclas y acciones
	keyActionMap->InsertKeyAction(SDLK_UP, "jump");
	keyActionMap->InsertKeyAction(SDLK_RIGHT, "move_right");
	keyActionMap->InsertKeyAction(SDLK_LEFT, "move_left");

	// Cargar Texturas
	assetStore->AddTexture("terrain_img", "./assets/img/terrain.png", renderer);
	assetStore->AddTexture("frog_idle", "./assets/img/frog_idle.png", renderer);
	assetStore->AddTexture("frog_run", "./assets/img/frog_run.png", renderer);
	assetStore->AddTexture("frog_fall", "./assets/img/frog_fall.png", renderer);
	assetStore->AddTexture("frog_jump", "./assets/img/frog_jump.png", renderer);

	// Add animation info5rmation
	animationManager->AddAnimation("player", "idle", "frog_idle", 32, 32, 11, 1, 15, true);
	animationManager->AddAnimation("player", "run", "frog_run", 32, 32, 12, 1, 15, true);
	animationManager->AddAnimation("player", "fall", "frog_fall", 32, 32, 1, 1, 1, true);
	animationManager->AddAnimation("player", "jump", "frog_jump", 32, 32, 1, 1, 1, true);

	// Agregar Sistemas
	//manager->AddSystem<MouseControllerSystem>();
	//manager->AddSystem<CollisionSystem>();
	//manager->AddSystem<DamageSystem>();
	manager->AddSystem<KeyboardControllerSystem>(eventManager, keyActionMap);
	manager->AddSystem<RenderBoxColliderSystem>();
	manager->AddSystem<RenderSystem>();
	manager->AddSystem<OverlapSystem>();
	manager->AddSystem<MovementSystem>();
	manager->AddSystem<WeightForceSystem>();
	manager->AddSystem<CollisionSystem>();
	manager->AddSystem<PlayerActionSystem>();
	manager->AddSystem<AnimationSystem>();
	manager->AddSystem<PlayerStateSystem>();

	LoadLevelMap("./assets/levels/level_01.tmx");

	Entity player = manager->CreateEntity();
	player.AddTag("player");
	player.AddComponent<AnimationComponent>(11, 1, 15, true);
	player.AddComponent<TransformComponent>(glm::vec2(300.0f, 50.0f));
	player.AddComponent<RigidbodyComponent>(false, 5.0f, 50.0f * 64);
	player.AddComponent<SpriteComponent>("frog_idle", 32, 32, 0, 0);
	player.AddComponent<BoxColliderComponent>(32, 32);
	player.AddComponent<PlayerDataComponent>(glm::vec2(0, -1200.0f * 64), 
		3.0f * 64);
}

void Game::processInput() {
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			this->isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				this->isRunning = false;
			} else if (sdlEvent.key.keysym.sym == SDLK_d) {
				debugMode = !debugMode;
			}
			eventManager->EmitteEvent<KeyboardEvent>(true, sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			eventManager->EmitteEvent<KeyboardEvent>(false, sdlEvent.key.keysym.sym);
			break;
		case SDL_MOUSEMOTION:
			int x, y;
			SDL_GetMouseState(&x, &y);
			//eventManager->EmitteEvent<MouseMotionEvent>(glm::vec2(x, y));
			break;
		default:
			break;
		}
	}
}

void Game::update() {
	// Calcular la espera; SDL_GetTicks retorna la cantidad de milisegundos que 
	// pasado desde que inicio SDL; https://wiki.libsdl.org/SDL2/SDL_GetTicks
	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - this->mPrvsFrame);

	if (0 < timeToWait && timeToWait <= MILLISECS_PER_FRAME) {
		SDL_Delay(timeToWait);
	}

	// Calculo de deltaTime; Division entre 1000 para que deltaTime sea en segundos
	double deltaTime = (SDL_GetTicks() - this->mPrvsFrame) / 1000.0;

	this->mPrvsFrame = SDL_GetTicks();

	// Limpiar los subscriptores
	eventManager->Clear();

	// Subscribirnos a eventos
	manager->GetSystem<KeyboardControllerSystem>().SubscribeToKeyboardEvent(
		eventManager);
	manager->GetSystem<PlayerActionSystem>().SubscribeToActionEvent(eventManager);
	manager->GetSystem<OverlapSystem>().SubscribeToCollisionEvent(eventManager);
	//manager->GetSystem<DamageSystem>().SubscribeToCollisionEvent(eventManager);
	//manager->GetSystem<MouseControllerSystem>().SubscribeToMouseMotionEvent(
	//	eventManager);

	//Ejecutar funcion update
	manager->GetSystem<WeightForceSystem>().Update();
	manager->GetSystem<MovementSystem>().Update(deltaTime);
	manager->GetSystem<CollisionSystem>().Update(eventManager);
	manager->GetSystem<PlayerStateSystem>().Update(animationManager);
	manager->GetSystem<AnimationSystem>().Update();


	manager->Update();
}

void Game::run() {
	Setup();

	while (this->isRunning) {
		processInput();
		update();
		render();
	}
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
	SDL_RenderClear(this->renderer);

	manager->GetSystem<RenderSystem>().Update(renderer, assetStore);
	if (debugMode) {
		manager->GetSystem<RenderBoxColliderSystem>().Update(renderer);
	}


	SDL_RenderPresent(this->renderer);
}

void Game::destroy() {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	/*
	for (int index = 0; index < entitiesVector.size(); index++) {
		SDL_DestroyTexture(this->entitiesVector[index].imgTexture);
		SDL_DestroyTexture(this->entitiesVector[index].txtTexture);
	}

	TTF_CloseFont(ttfFont);

	TTF_Quit();
	*/
	SDL_Quit();
}

