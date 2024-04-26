#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Vec2.h"
#include "StupidPtr.h"

int main() {
	std::cout << "Lab 02: RAII" << std::endl;

	if (true) {
		//Vec2* pos = new Vec2(2, 2);
		//std::cout << pos->toString() << std::endl;
		
	}

	//delete pos;
	StupidPtr<Vec2> pos = StupidPtr<Vec2>(2, 2);
	std::cout << pos->toString() << std::endl;


	return 0;
}