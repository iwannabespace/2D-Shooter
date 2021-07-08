#pragma once

class Coord
{
public:
	float x, y;
public:
	Coord();
	Coord(float x, float y);
	~Coord();
	bool operator==(Coord rhs) const; // returns true if two Coords are the same
	bool operator!=(Coord rhs) const; // returns true if two Coords are not the same
};