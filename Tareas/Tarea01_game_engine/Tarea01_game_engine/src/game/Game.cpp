#include "Game.h"
#include <iostream>
#include <fstream>

Game::Game() {
	std::cout << "Se ejecuta el constructor de GAME" << std::endl;
}

Game::~Game() {
	std::cout << "Se ejecuta el destructor de GAME" << std::endl;
}

void Game::init() {
	std::string nombreArchivo = "config.txt";
	std::ifstream archivoEntrada(nombreArchivo);
	std::string etiqueta;

	// Inicializar SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error al inicializar SDL" << std::endl;
		return;
	}
	if (TTF_Init() < 0) {
		std::cout << "Error al inicializar SDL_TTF" << std::endl;
		return;
	}

	// Lectura de datos para la ventana
	archivoEntrada >> etiqueta;
	if (etiqueta.compare("window") == 0) {
		archivoEntrada >> this->windowWidth >> this->windowHeight >> 
			this->windowColor.r >> this->windowColor.g >> this->windowColor.b;
	}

	// Crear la ventana
	this->window = SDL_CreateWindow(
		"Lab 04: Intro al motor de videojuegos",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->windowWidth,
		this->windowHeight,
		SDL_WINDOW_SHOWN
	);

	//Crear el renderer
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	archivoEntrada >> etiqueta;
	if (etiqueta.compare("font") == 0) {
		archivoEntrada >> this->font.address >> this->font.r >> this->font.g
			>> this->font.b >> this->font.size;
		this->fontColor.r = this->font.r;
		this->fontColor.g = this->font.g;
		this->fontColor.b = this->font.b;
	}
	archivoEntrada >> etiqueta;
	bool exit = true;
	while (etiqueta.compare("entity") == 0 && exit) {
		Entity entity;
		archivoEntrada >> entity.name >> entity.directory >> entity.imgWidth
			>> entity.imgHeight >> entity.pos.x >> entity.pos.y
			>> entity.imgVel.x >> entity.imgVel.y >> entity.angle;

		entity.imgSurface = IMG_Load(entity.directory.c_str());
		entity.imgTexture = SDL_CreateTextureFromSurface(this->renderer, entity.imgSurface);
		SDL_FreeSurface(entity.imgSurface);

		entity.imgDstRect.x = entity.pos.x;
		entity.imgDstRect.y = entity.pos.y;
		entity.imgDstRect.w = entity.imgWidth;
		entity.imgDstRect.h = entity.imgHeight;

		entity.srcRect.x = 0; //Borrar
		entity.srcRect.y = 0; //Borrar
		entity.srcRect.w = entity.imgWidth;
		entity.srcRect.h = entity.imgHeight;

		// Cargar texto
		entity.message = entity.name;
		this->ttfFont = TTF_OpenFont(this->font.address.c_str(), this->font.size);
		SDL_Surface* txtSurface = TTF_RenderText_Solid(this->ttfFont,
			entity.message.c_str(),
			this->fontColor
		);
		
		entity.txtTexture = SDL_CreateTextureFromSurface(this->renderer, txtSurface);
		entity.txtWidth = txtSurface->w;
		entity.txtHeight = txtSurface->h;
		float centerOfImageX = (entity.pos.x) + (entity.imgWidth / 2);
		entity.txtPos.x = centerOfImageX - (entity.txtWidth / 2);
		float centerOfImageY = (entity.pos.y) + (entity.imgHeight / 2);
		entity.txtPos.y = centerOfImageY - (entity.txtHeight / 2);
		entity.txtAngle = 0.0;
		SDL_FreeSurface(txtSurface);
		
		entitiesVector.push_back(entity);
		etiqueta = "";
		archivoEntrada >> etiqueta;
		if (etiqueta == "") {
			exit = false;
		}
	}

	// Cargar texto
	this->ttfFont = TTF_OpenFont(this->font.address.c_str(), this->font.size);

	this->isRunning = true;

	// Inicializar datos del texto
	this->message = "Lab 04: Intro al motor de videojuegos";
	this->fontColor.r = 255;
	SDL_Surface* txtSurface = TTF_RenderText_Solid(this->ttfFont,
		this->message.c_str(),
		this->fontColor
	);
	this->txtTexture = SDL_CreateTextureFromSurface(this->renderer, txtSurface);
	this->txtWidth = txtSurface->w;
	this->txtHeight = txtSurface->h;
	this->txtPos.x = (this->windowWidth / 2) - (this->txtWidth / 2);
	this->txtPos.y = 20;
	SDL_FreeSurface(txtSurface);
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

	// Calculo de deltaTime
	// Dividimos entre 1000 porque queremos que deltaTime ese en segundos
	double deltaTime = (SDL_GetTicks() - this->mPrvsFrame) / 1000.0;

	this->mPrvsFrame = SDL_GetTicks();

	for (int index = 0; index < entitiesVector.size(); index++) {
		this->entitiesVector[index].pos.x += this->entitiesVector[index].imgVel.x * deltaTime;
		this->entitiesVector[index].pos.y += this->entitiesVector[index].imgVel.y * deltaTime;

		if (this->entitiesVector[index].pos.x + this->entitiesVector[index].imgWidth >= this->windowWidth 
			|| this->entitiesVector[index].pos.x <= 0.0) {
			this->entitiesVector[index].imgVel.x = this->entitiesVector[index].imgVel.x * -1;
		}

		if (this->entitiesVector[index].pos.y + this->entitiesVector[index].imgHeight >= this->windowHeight 
			|| this->entitiesVector[index].pos.y <= 0.0) {
			this->entitiesVector[index].imgVel.y = this->entitiesVector[index].imgVel.y * -1;
		}

		float centerOfImageX = (this->entitiesVector[index].pos.x) + 
			(this->entitiesVector[index].imgWidth / 2);
		this->entitiesVector[index].txtPos.x = centerOfImageX - 
			(this->entitiesVector[index].txtWidth / 2);
		
		float centerOfImageY = (this->entitiesVector[index].pos.y) + 
			(this->entitiesVector[index].imgHeight / 2);
		this->entitiesVector[index].txtPos.y = centerOfImageY - 
			(this->entitiesVector[index].txtHeight / 2);
	}

}

void Game::render() {
	SDL_SetRenderDrawColor(renderer,
		this->windowColor.r,
		this->windowColor.g,
		this->windowColor.b,
		this->windowColor.a
	);
	SDL_RenderClear(this->renderer);

	this->entitiesVector[0].angle = 0.0;
	for (int index = 0; index < entitiesVector.size(); index++) {
		this->entitiesVector[index].imgDstRect.x = this->entitiesVector[index].pos.x;
		this->entitiesVector[index].imgDstRect.y = this->entitiesVector[index].pos.y;
		this->entitiesVector[index].imgDstRect.w = this->entitiesVector[index].imgWidth;
		this->entitiesVector[index].imgDstRect.h = this->entitiesVector[index].imgHeight;

		this->entitiesVector[index].txtDstRect.x = this->entitiesVector[index].txtPos.x;
		this->entitiesVector[index].txtDstRect.y = this->entitiesVector[index].txtPos.y;
		this->entitiesVector[index].txtDstRect.w = this->entitiesVector[index].txtWidth;
		this->entitiesVector[index].txtDstRect.h = this->entitiesVector[index].txtHeight;


		// Dibujar imagen
		// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx
		SDL_RenderCopyEx(
			this->renderer,
			this->entitiesVector[index].imgTexture,
			&this->entitiesVector[index].srcRect,
			&this->entitiesVector[index].imgDstRect,
			this->entitiesVector[index].angle,
			NULL,
			SDL_FLIP_NONE
		);

		SDL_RenderCopyEx(
			this->renderer,
			this->entitiesVector[index].txtTexture,
			NULL, // Si es NULL dibuja toda la textura
			&this->entitiesVector[index].txtDstRect,
			this->entitiesVector[index].txtAngle,
			NULL,
			SDL_FLIP_NONE
		);
	}

	SDL_Rect txtDstRect = {
		this->txtPos.x,
		this->txtPos.y,
		this->txtWidth,
		this->txtHeight
	};

	SDL_RenderCopyEx(
		this->renderer,
		this->txtTexture,
		NULL, // Si es NULL dibuja toda la textura
		&txtDstRect,
		this->txtAngle,
		NULL,
		SDL_FLIP_NONE
	);

	SDL_RenderPresent(this->renderer);
}

void Game::run() {
	while (this->isRunning) {
		processInput();
		update();
		render();
	}
}

void Game::destroy() {
	SDL_DestroyTexture(this->txtTexture);
	for (int index = 0; index < entitiesVector.size(); index++) {
		SDL_DestroyTexture(this->entitiesVector[index].imgTexture);
	}

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	TTF_Quit();
	SDL_Quit();
}