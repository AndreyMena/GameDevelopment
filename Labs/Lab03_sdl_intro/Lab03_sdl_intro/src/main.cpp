#include <iostream>
#include <SDL.h>

using namespace std;

// Recordar agregar los parametros de la subrutina
//main para que funcione SDL
int main(int argc, char* argv[]) {
	cout << "Lab 03: Intro a SDL" << endl;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	size_t width = 800;
	size_t heigth = 600;

	bool isRunning = true;

	// Registro que almacena los datos del rectangulo
	// https://wiki.libsdl.org/SDL2/SDL_Rect
	SDL_Rect rect = {
		(width / 2) -25,
		(heigth / 2) - 25,
		50,
		50
	};

	// Inicializar SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Error inicializando SDL" << endl;
		return 1;
	}

	// Creacion de la ventana
	//https://wiki.libsdl.org/SDL2/SDL_CreateWindow
	window = SDL_CreateWindow(
		"Lab 03: Intro a SDL", // Titulo de la ventana
		SDL_WINDOWPOS_CENTERED, // Posicion x en la pantalla
		SDL_WINDOWPOS_CENTERED,  // Posicion y en la pantalla
		width, // Ancho en la ventana
		heigth, // Alto en la ventana
		SDL_WINDOW_SHOWN // Flags: https://wiki.libsdl.org/SDL2/SDL_WindowFlags
	);

	// Crear el renderer (se encarga de dibujar en la ventana)
	// https://wiki.libsdl.org/SDL2/SDL_CreateRenderer
	renderer = SDL_CreateRenderer(
		window, // Ventana en la que va a dibujar
		-1, // Driver de la pantalla, Indice del renderer driver, -1 para inicializar la primer flag requerida
		0 // Flags: https://wiki.libsdl.org/SDL2/SDL_RendererFlags
	);

	while (isRunning) {
		// Registro que almacena los datos de un evento
		SDL_Event sdlEvent;

		// SDL_PollEvent Saca de la cola de eventos de SDL un evento pendiente
		// y lo almacena en un registro de tipo SDL_Event
		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
			case SDL_QUIT: // Se presiono el boton de cerrar ventana
				isRunning = false;
				break;
			case SDL_KEYDOWN: // Se presiono una tecla
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
				}
				break;
			default:
				break;
			}
		}

		// Establece los colores con los que se va a dibujar
		// https://wiki.libsdl.org/SDL2/SDL_SetRenderDrawColor
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

		// Limpia la ventana con el color pre establecido
		// https://wiki.libsdl.org/SDL2/SDL_RenderClear
		SDL_RenderClear(renderer);

		
		// Dibuja en la ventana un rectangulo
		// https://wiki.libsdl.org/SDL2/SDL_RenderFillRect
		SDL_RenderFillRect(renderer, &rect);

		// Actualiza la ventana
		// https://wiki.libsdl.org/SDL2/SDL_RenderPresent
		SDL_RenderPresent(renderer);
	}

	//Liberar recursos
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}