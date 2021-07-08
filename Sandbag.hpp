#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Object.hpp"
#include "Coord.hpp"

class Sandbag : public Object // publicly inherits from 'Object' class 
{
public:
	void init(sf::RenderWindow* window, const std::string& texturePath, Coord pos) override;
	void paint() const override;
	Coord getPosition() const;
	sf::Sprite getSandbag() const; // Returns the sprite of Sandbag
};