#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Color {
	std::string nombre;
	int r, g, b;
};

int main() {
	std::cout << "Lab 00: Lectura de archivos" << std::endl;

	std::string nombreArchivo = "colores.txt";
	std::ifstream archivoEntrada(nombreArchivo);

	std::vector<Color> colores;

	std::string etiqueta;

	while (archivoEntrada >> etiqueta) {
		Color color;
		if (etiqueta.compare("color") == 0) {
			archivoEntrada >> color.nombre;
			archivoEntrada >> color.r >> color.g >> color.b;
			colores.push_back(color);
		}
	}

	for (const auto& color : colores) {
		std::cout << color.nombre << " (" << color.r << ", " << color.g << " ,"
			<< color.b << ")" << std::endl;
	}

	return 0;
}