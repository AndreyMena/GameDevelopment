#include "game/Game.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	cout << "Tarea 01: Intro al motor SDL" << endl;
	



	Game game;
	game.init();
	game.run();
	game.destroy();

	return 0;
}