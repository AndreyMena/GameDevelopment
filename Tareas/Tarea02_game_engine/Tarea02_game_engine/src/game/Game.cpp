#include "Game.h"

#include "../Components/CircleColliderComponent.h"
#include "../Components/MouseControllerComponent.h"
#include "../Components/KeyboardControllerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"

#include "../Events/KeyboardEvent.h"
#include "../Events/MouseMotionEvent.h"

#include "../Systems/CollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardControllerSystem.h"
#include "../Systems/MouseControllerSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"

#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <string>

Game::Game() {
	assetStore = std::make_shared<AssetStore>();
	manager = std::make_shared<ECSManager>();
	eventManager = std::make_shared<EventManager>();
	std::cout << "Se ejecuta el constructor de GAME" << std::endl;
}

Game::~Game() {
	std::cout << "Se ejecuta el destructor de GAME" << std::endl;
}

void Game::initWindow(std::ifstream& archivoEntrada) {
	// Lectura de datos para la ventana
	archivoEntrada >> this->windowWidth >> this->windowHeight;

	// Crear la ventana
	this->window = SDL_CreateWindow("Tarea 02: Motor de videojuegos",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->windowWidth,
		this->windowHeight, SDL_WINDOW_SHOWN);
	// TODO: Verificar que se crea la ventana

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	// TODO: Verificar que se crea el renderer
}

void Game::setTextures(std::ifstream& archivoEntrada, std::string& etiqueta) {
	// Lectura de datos para la ventana
	std::string typeOfAsset;
	archivoEntrada >> typeOfAsset;

	std::string assetId;
	std::string address;
	std::size_t size;

	if (typeOfAsset.compare("font") == 0) {
		archivoEntrada >> assetId >> address >> size;
		assetStore->AddFont(assetId, address, size, renderer);
	}else if(typeOfAsset.compare("image") == 0) {
		archivoEntrada >> assetId >> address >> size;
		assetStore->AddTexture(assetId, address, renderer);
	}
}

void Game::readInput() {
	std::ifstream archivoEntrada(this->fileConfig);
	bool exit = true;
	std::string etiqueta;
	archivoEntrada >> etiqueta;
	while (exit) {
		if (etiqueta.compare("window") == 0) {
			this->initWindow(archivoEntrada);
		} else if (etiqueta == "asset") {
			this->setTextures(archivoEntrada, etiqueta);
		}
		else if (etiqueta == "player") {

		}
		else if (etiqueta == "bullet") {

		}
		else if (etiqueta == "enemy") {

		}

		etiqueta = "";
		archivoEntrada >> etiqueta;
		if (etiqueta == "") {
			exit = false;
		}
	}
}

void Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error al inicializar SDL" << std::endl;
		return;
	}

	std::ifstream archivoEntrada(this->fileConfig);
	std::string etiqueta;
	archivoEntrada >> etiqueta;
	//this->readInput();

	this->initWindow(archivoEntrada);

	isRunning = true;
}


void Game::Setup() {
	// Agregar Sistema
	manager->AddSystem<KeyboardControllerSystem>();
	manager->AddSystem<RenderSystem>();
	manager->AddSystem<MovementSystem>();
	manager->AddSystem<CollisionSystem>();
	manager->AddSystem<DamageSystem>();
	manager->AddSystem<MouseControllerSystem>();

	// Cargar Texturas
	
	assetStore->AddTexture("ship-img", "./assets/img/ship.png", renderer);


	// Creacion de entidades
	Entity s01 = manager->CreateEntity();
	s01.AddComponent<CircleColliderComponent>(16.0f);
	s01.AddComponent<KeyboardControllerComponent>();
	s01.AddComponent<RigidbodyComponent>(glm::vec2(0.0, 0.0), 150.0f);
	s01.AddComponent<SpriteComponent>("ship-img", 16, 16, 16, 0);
	s01.AddComponent<TransformComponent>(glm::vec2(100.0f, 100.0f), 
		glm::vec2(2.0, 2.0), 0.0);
	s01.AddComponent<MouseControllerComponent>();

	/*Entity s02 = manager->CreateEntity();
	s02.AddComponent<CircleColliderComponent>(16);
	s02.AddComponent<RigidbodyComponent>(glm::vec2(-50, 0));
	s02.AddComponent<SpriteComponent>("ship-img", 16, 16, 16, 0);
	s02.AddComponent<TransformComponent>(glm::vec2(700, 100), glm::vec2(2, 2), 0);*/
	
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
			}
			eventManager->EmitteEvent<KeyboardEvent>(true, sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			eventManager->EmitteEvent<KeyboardEvent>(false, sdlEvent.key.keysym.sym);
			break;
		case SDL_MOUSEMOTION:
			int x, y;
			SDL_GetMouseState(&x, &y);
			eventManager->EmitteEvent<MouseMotionEvent>(glm::vec2(x, y));
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
	manager->GetSystem<DamageSystem>().SubscribeToCollisionEvent(eventManager);
	manager->GetSystem<MouseControllerSystem>().SubscribeToMouseMotionEvent(
		eventManager);

	//Ejecutar funcion update
	manager->GetSystem<MovementSystem>().Update(static_cast<float>(deltaTime));
	manager->GetSystem<CollisionSystem>().Update(eventManager);

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

