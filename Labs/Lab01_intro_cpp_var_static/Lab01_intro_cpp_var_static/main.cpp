#include "Persona.h"
#include <iostream>

using namespace std;

int main() {
	cout << "Lab 01: Variables estaticas y plantillas" << endl;
	cout << Persona<Musico>::getId() << endl;
	cout << Persona<Artista>::getId() << endl;
	cout << Persona<Musico>::getId() << endl;
	cout << Persona<Artista>::getId() << endl;
	cout << Persona<Empleado>::getId() << endl;
	cout << Persona<Empleado>::getId() << endl;
	cout << Persona<Empleado>::getId() << endl;
	return 0;
}
