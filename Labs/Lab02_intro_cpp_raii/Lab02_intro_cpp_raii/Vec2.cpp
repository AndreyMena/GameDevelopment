#include "Vec2.h"

std::string Vec2::toString() const {
	std::stringstream result;
	result << "(" << x << ", " << y << ")";
	return result.str();

}
