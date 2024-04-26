#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <sstream>
#include <string>

class Vec2 {
private:
	int x = 0;
	int y = 0;
public:
	Vec2(int x, int y) : x(x), y(y) {
		std::cout << "Se ejecuta contructor de Vec2" << std::endl;
	};

	~Vec2() {
		std::cout << "Se ejecuta destructor de Vec2" << std::endl;
	};

	std::string toString() const;
};


#endif // !VEC2_H

