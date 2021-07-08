#pragma once

#include <SFML/Graphics.hpp>
#include "Coord.hpp"

class Object
{
protected: 
	sf::RenderWindow* window;
	sf::Texture texture;
	sf::Sprite sprite;
	Coord pos;
protected:
	virtual void init(sf::RenderWindow* window, const std::string& texturePath, Coord pos) = 0; // These two functions are marked as pure virtual because all the sub classes of this class will need them.
	virtual void paint() const = 0;
};