#include "Game.h"

#include "../Events/KeyboardEvent.h"
#include "../Events/MouseMotionEvent.h"

#include "../Systems/AnimationSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/CircularCollisionSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/OverlapSystem.h"
#include "../Systems/RenderBoxColliderSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/ScriptSystem.h"
#include "../Systems/WeightForceSystem.h"
#include "../Systems/ProjectileEmitterSystem.h"
#include "../Systems/GameStateSystem.h"
#include "../Systems/MouseControllerSystem.h"
#include "../Systems/RenderBackgroundSystem.h"

#include "../Events/MouseMotionEvent.h"
#include "../Events/MouseClickEvent.h"

#include <cstdio>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

size_t Game::windowWidth;
size_t Game::windowHeight;
size_t Game::mapWidth;
size_t Game::mapHeight;

Game::Game() {
	animationManager = std::make_shared<AnimationManager>();
	assetStore = std::make_shared<AssetStore>();
	manager = std::make_shared<ECSManager>();
	eventManager = std::make_shared<EventManager>();
	controllerManager = std::make_shared<ControllerManager>();
	levelLoader = std::make_shared<LevelLoader>();

	std::cout << "Se ejecuta el constructor de GAME" << std::endl;
}

Game::~Game() {
	std::cout << "Se ejecuta el destructor de GAME" << std::endl;
}

Game& Game::GetInstance() {
	static Game game;
	return game;
}

void Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error al inicializar SDL" << std::endl;
		return;
	}

	windowWidth = 768;//480;  // 800
	windowHeight = 416;//320;  // 600

	this->window = SDL_CreateWindow(
		"Tarea03: Motor de videojuegos con LUA",
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
	camera.x = 0;
	camera.y = 0;
	camera.w = windowWidth;
	camera.h = windowHeight;

	isRunning = true;
}

void Game::NextLevel() {
	levelLoader->LoadNextLevel(lua, controllerManager, assetStore,
		renderer, animationManager, manager);
}

void Game::ReloadLevel() {
	levelLoader->ReloadLevel(lua, controllerManager, assetStore,
		renderer, animationManager, manager);
}

void Game::Setup() {
	// Agregar Sistemas
	manager->AddSystem<AnimationSystem>();
	manager->AddSystem<CameraMovementSystem>();
	manager->AddSystem<CollisionSystem>();
	manager->AddSystem<MovementSystem>();
	manager->AddSystem<OverlapSystem>();
	manager->AddSystem<RenderBoxColliderSystem>();
	manager->AddSystem<RenderSystem>();
	manager->AddSystem<ScriptSystem>();
	manager->AddSystem<WeightForceSystem>();
	manager->AddSystem<GameStateSystem>();
	manager->AddSystem<MouseControllerSystem>();
	manager->AddSystem<RenderBackgroundSystem>();

	manager->GetSystem<ScriptSystem>().CreateLuaBindings(lua);

	lua.open_libraries(sol::lib::base);

	levelLoader->LoadLevels("./assets/scripts/game_levels.lua", lua);

	levelLoader->LoadLevel(lua, controllerManager, assetStore, 
		renderer, animationManager, manager);

	manager->AddSystem<ProjectileEmitterSystem>(manager, lua);
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
			} else if (sdlEvent.key.keysym.sym == SDLK_y) {

				//manager->KillAllEntities();

				levelLoader->LoadLevel(lua, controllerManager, assetStore,
					renderer, animationManager, manager);
			}else {
				if (controllerManager->IskeyMapped(sdlEvent.key.keysym.sym)) {
					std::string action = controllerManager->GetAction(
						sdlEvent.key.keysym.sym);
					controllerManager->ActivateAction(action);
				}
			}
			break;
		case SDL_KEYUP:
			if (controllerManager->IskeyMapped(sdlEvent.key.keysym.sym)) {
				std::string action = controllerManager->GetAction(
					sdlEvent.key.keysym.sym);
				controllerManager->DeactivateAction(action);
			}
			break;
		case SDL_MOUSEMOTION:
			int x, y;
			SDL_GetMouseState(&x, &y);
			//eventManager->EmitteEvent<MouseMotionEvent>(glm::vec2(x, y));
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
				eventManager->EmitteEvent<MouseClickEvent>(
					glm::vec2(sdlEvent.button.x, sdlEvent.button.y));
			}
			/*
			if (sdlEvent.button.button == SDL_BUTTON_RIGHT) {
				eventManager->EmitteEvent<MouseRightClickEvent>(
					glm::vec2(sdlEvent.button.x, sdlEvent.button.y));
			}
			*/
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
	//manager->GetSystem<MouseControllerSystem>().SubscribeToMouseClickEvent(
	//	eventManager);
	manager->GetSystem<OverlapSystem>().SubscribeToCollisionEvent(eventManager);
	manager->GetSystem<ProjectileEmitterSystem>().SubscribeToProjectileEvent(
		eventManager);
	manager->GetSystem<GameStateSystem>().SubscribeToOnLevelEvent(eventManager);

	//Ejecutar funcion update
	manager->GetSystem<ScriptSystem>().Update(lua);

	manager->GetSystem<WeightForceSystem>().Update();
	manager->GetSystem<MovementSystem>().Update(deltaTime);
	manager->GetSystem<CollisionSystem>().Update(eventManager, lua);
	manager->GetSystem<CameraMovementSystem>().Update(camera);

	manager->GetSystem<ScriptSystem>().Awake(lua, manager);
	manager->GetSystem<AnimationSystem>().Update();
	manager->Update();
}

void Game::run() {
	Setup();

	while (this->isRunning) {
		processMenu();
		renderMenu();
		while (this->isPlaying) {
			processInput();
			update();
			render();
		}
	}
}

void Game::processMenu() {
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
				eventManager->EmitteEvent<MouseClickEvent>(
					glm::vec2(sdlEvent.button.x, sdlEvent.button.y));
			}
			break;
		default:
			break;
		}
	}
}

void Game::renderMenu() {
	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - this->mPrvsFrame);

	if (0 < timeToWait && timeToWait <= MILLISECS_PER_FRAME) {
		SDL_Delay(timeToWait);
	}
	double deltaTime = (SDL_GetTicks() - this->mPrvsFrame) / 1000.0;

	this->mPrvsFrame = SDL_GetTicks();
	eventManager->Clear();

	manager->GetSystem<MouseControllerSystem>().SubscribeToMouseClickEvent(
		eventManager);

	//Background
	SDL_Rect menu;
	menu.x = 0;
	menu.y = 0;
	menu.w = 768;
	menu.h = 416;
	SDL_RenderCopy(renderer, this->assetStore->GetTexture("ghoticvania_menu"), NULL, &menu);

	SDL_RenderPresent(this->renderer);

}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
	SDL_RenderClear(this->renderer);

	manager->GetSystem<RenderBackgroundSystem>().Update(renderer, assetStore, windowWidth, windowHeight);

	manager->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);
	if (debugMode) {
		manager->GetSystem<RenderBoxColliderSystem>().Update(renderer);
	}

	manager->GetSystem<GameStateSystem>().Update(renderer, assetStore, windowWidth, windowHeight);

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

	*/
	SDL_Quit();
}

