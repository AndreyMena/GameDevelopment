#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>
#include "./Game/Game.H"

int main(int argc, char* argv[]) {
	std::cout << "Tarea 02: Motor de videojuegos" << std::endl;
	
	Game game;
	game.init();
	game.run();
	game.destroy();

	return 0;
}