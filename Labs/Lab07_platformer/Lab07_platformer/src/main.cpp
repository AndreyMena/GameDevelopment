#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>
#include "./Game/Game.H"
#include <sol/sol.hpp>
#include <string>

void TestLua() {
	sol::state lua;
	lua.open_libraries(sol::lib::base);
	
	lua.script_file("./assets/scripts/script_01.lua");

	//Obtener una vairable de LUA

	std::string nombre = lua["var_txt"];
	std::cout << "C++ -> Hola " << nombre << std::endl;


}

int main(int argc, char* argv[]) {
	std::cout << "Lab 05: Motor de videojuegos" << std::endl;
	

	TestLua();
	/*
	Game game;
	game.init();
	game.run();
	game.destroy();
	*/
	return 0;
}