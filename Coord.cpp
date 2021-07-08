#include "Coord.hpp"

Coord::Coord()
	: x(0.0f), y(0.0f)
{
}

Coord::Coord(float x, float y)
	: x(x), y(y)
{
}

Coord::~Coord()
{
}

bool Coord::operator==(Coord rhs) const
{
	return (x == rhs.x && y == rhs.y); // Return if x is equal to rhs.x and y is equal to rhs.y
}

bool Coord::operator!=(Coord rhs) const
{
	return !operator==(rhs); // Return the opposite of '==' operator
}