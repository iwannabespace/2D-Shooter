#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Object.hpp"
#include "Coord.hpp"

class Barrel : public Object
{
private:
	bool isVisible;
public:
	void init(sf::RenderWindow* window, const std::string& texturePath, Coord pos) override;
	void paint() const override;
	void setVisible(bool isVisible);
	bool getVisible() const;
	Coord getPosition() const;
	sf::Sprite getBarrel() const; // returns the sprite of Barrel
};