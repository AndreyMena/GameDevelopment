#include "Game.h"

#include "../Components/CircleColliderComponent.h"
#include "../Components/MouseControllerComponent.h"
#include "../Components/KeyboardControllerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/EnemyGeneratorComponent.h"

#include "../Events/KeyboardEvent.h"
#include "../Events/MouseMotionEvent.h"

#include "../Systems/CollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardControllerSystem.h"
#include "../Systems/MouseControllerSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/EnemyGeneratorSystem.h"

#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <string>
#include <ctime>
#include <cstdlib>

Game::Game() {
	srand(time(0));  // Initialize random number generator.

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
		int width;
		int height;
		archivoEntrada >> assetId >> address >> width >> height;
		assetStore->AddTexture(assetId, address, renderer, width, height);
	}
}
void Game::addPlayer(std::ifstream& archivoEntrada) {
	std::string textureId;
	int lifes;
	int speed;
	float scale = 2.0;
	archivoEntrada >> textureId >> lifes >> speed;
	
	Image image = this->assetStore->GetImage(textureId);

	Entity player = manager->CreateEntity();
	player.AddComponent<CircleColliderComponent>(16.0f);
	player.AddComponent<KeyboardControllerComponent>();
	player.AddComponent<RigidbodyComponent>(glm::vec2(0.0, 0.0), speed);
	player.AddComponent<SpriteComponent>(textureId, image.width, image.height, image.width, 0);
	glm::vec2 position;
	position.x = (this->windowWidth / 2) - (image.width / 2);
	position.y = (this->windowHeight / 2) - (image.height / 2);

	player.AddComponent<TransformComponent>(position,
		glm::vec2(scale, scale), 0);
	player.AddComponent<MouseControllerComponent>();
}

void Game::addEnemy(std::ifstream& archivoEntrada) {
	std::string textureId;
	int score;
	int minSpeed;
	int maxSpeed;
	int intSpawnRate;
	archivoEntrada >> textureId >> score >> minSpeed >> maxSpeed >>
		intSpawnRate;
	double spawnRate; // La variable donde almacenaremos el valor convertido

	// Convertir el entero a double
	spawnRate = static_cast<double>(intSpawnRate);

	float speed = rand() % maxSpeed + minSpeed;
	float speedX = rand() % maxSpeed + minSpeed;
	float speedY = rand() % maxSpeed + minSpeed;

	Image image = this->assetStore->GetImage(textureId);
	float scale = 2.0;
	glm::vec2 position;
	int maxWidth = windowWidth - (image.width * scale);
	int maxHeight = windowHeight - (image.height * scale);
	position.x = rand() % maxWidth;
	position.y = rand() % maxHeight;
	std::cout << position.x << " "<< position.y << std::endl;

	Entity enemy = manager->CreateEntity();
	enemy.AddComponent<CircleColliderComponent>(16.0f);
	enemy.AddComponent<RigidbodyComponent>(glm::vec2(speedX, speedY), speed);
	enemy.AddComponent<SpriteComponent>(textureId, image.width, image.height, image.width, 0);
	enemy.AddComponent<TransformComponent>(position,
		glm::vec2(scale, scale), 0);
	enemy.AddComponent<EnemyGeneratorComponent>(textureId, image, score,
		minSpeed, maxSpeed, spawnRate, 0.0);
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
			this->addPlayer(archivoEntrada);
		}
		else if (etiqueta == "bullet") {
			// TODO
			std::string todo;
			archivoEntrada >> todo >> todo;
		}
		else if (etiqueta == "enemy") {
			std::cout << "aaa" << std::endl;
			this->addEnemy(archivoEntrada);
			//std::string todo;
			//archivoEntrada >> todo >> todo >> todo >> todo >> todo;
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

	this->readInput();

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
	manager->AddSystem<EnemyGeneratorSystem>(windowWidth, windowHeight);
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
	
	//std::cout << this->a << std::endl;

	// Limpiar los subscriptores
	eventManager->Clear();

	// Subscribirnos a eventos
	manager->GetSystem<KeyboardControllerSystem>().SubscribeToKeyboardEvent(
		eventManager);
	manager->GetSystem<DamageSystem>().SubscribeToCollisionEvent(eventManager);
	manager->GetSystem<MouseControllerSystem>().SubscribeToMouseMotionEvent(
		eventManager);

	//Ejecutar funcion update
	manager->GetSystem<MovementSystem>().Update(static_cast<float>(deltaTime), windowWidth, windowHeight);
	manager->GetSystem<CollisionSystem>().Update(eventManager);
	manager->GetSystem<EnemyGeneratorSystem>().Update(deltaTime, this->manager);

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

