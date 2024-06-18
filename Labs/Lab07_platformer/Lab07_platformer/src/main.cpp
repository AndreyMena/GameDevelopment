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

	int edad = lua["var_num"];
	std::cout << "C++ -> Hola " << edad << std::endl;

	//Obtener datos de una tabla de LUA
	std::string titulo = lua["config"]["title"];
	std::cout << "C++ -> Datos de condiguracion " << std::endl;
	std::cout << "C++ -> Titulo " << titulo<< std::endl;
	
	//Guardar tabla de LUA en una variable
	sol::table config = lua["config"];
	bool pantallaCompleta = config["fullscreen"];
	int ancho = config["resolution"]["width"];
	int alto = config["resolution"]["height"];
	std::cout << "C++ -> Pantalla completa " << pantallaCompleta << std::endl;
	std::cout << "C++ -> Ancho " << ancho << std::endl;
	std::cout << "C++ -> Alto " << alto << std::endl;
	


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