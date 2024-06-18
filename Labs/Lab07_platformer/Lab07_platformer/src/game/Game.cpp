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

#include "../Events/KeyboardEvent.h"
#include "../Events/MouseMotionEvent.h"

#include "../Systems/CircularCollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardControllerSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/PlayerActionSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/MouseControllerSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/OverlapSystem.h"
#include "../Systems/PlayerStateSystem.h"
#include "../Systems/RenderBoxColliderSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/WeightForceSystem.h"

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
	keyActionMap = std::make_shared<KeyActionMap>();
	levelLoader = std::make_shared<LevelLoader>();

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

	windowWidth = 480;  // 800
	windowHeight = 320;  // 600

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
	camera.x = 0;
	camera.y = 0;
	camera.w = windowWidth;
	camera.h = windowHeight;

	isRunning = true;
}

void Game::Setup() {
	// Agregar Sistemas
	manager->AddSystem<AnimationSystem>();
	manager->AddSystem<CameraMovementSystem>();
	manager->AddSystem<CollisionSystem>();
	manager->AddSystem<KeyboardControllerSystem>(eventManager, keyActionMap);
	manager->AddSystem<MovementSystem>();
	manager->AddSystem<OverlapSystem>();
	manager->AddSystem<PlayerActionSystem>();
	manager->AddSystem<PlayerStateSystem>();
	manager->AddSystem<RenderBoxColliderSystem>();
	manager->AddSystem<RenderSystem>();
	manager->AddSystem<WeightForceSystem>();

	levelLoader->LoadLevel(keyActionMap, assetStore, renderer,
		animationManager, manager, "./assets/levels/level_02.tmx");

	Entity player = manager->CreateEntity();
	player.AddTag("player");
	player.AddComponent<AnimationComponent>(11, 1, 15, true);
	player.AddComponent<TransformComponent>(glm::vec2(300.0f, 50.0f));
	player.AddComponent<RigidbodyComponent>(false, 5.0f, 50.0f * 64);
	player.AddComponent<SpriteComponent>("frog_idle", 32, 32, 0, 0);
	player.AddComponent<BoxColliderComponent>(32, 32);
	player.AddComponent<PlayerDataComponent>(glm::vec2(0, -1200.0f * 64), 
		3.0f * 64);
	player.AddComponent<CameraFollowComponent>();
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

	//Ejecutar funcion update
	manager->GetSystem<WeightForceSystem>().Update();
	manager->GetSystem<MovementSystem>().Update(deltaTime);
	manager->GetSystem<CollisionSystem>().Update(eventManager);
	manager->GetSystem<PlayerStateSystem>().Update(animationManager);
	manager->GetSystem<AnimationSystem>().Update();
	manager->GetSystem<CameraMovementSystem>().Update(camera);


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

	manager->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);
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

