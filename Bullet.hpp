#pragma once

#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "Player.hpp"

class Player;
enum class WalkDirection;

class Bullet : public Object // publicly inherits from 'Object' class
{
private:
	float speed;
	float angle;
	Player* player; // This player object will give a poisition and a direction for bullet
	WalkDirection dir;
public:
	Bullet(Player* player);
	void update();
	void move(float speed);
	void setSpeed(float speed);
	void setPosition(Coord pos);
	void setDirection(WalkDirection dir);
	void init(sf::RenderWindow* window, const std::string& texturePath, Coord pos) override;
	void paint() const override;
	sf::Sprite& getSprite();
	WalkDirection getDirection() const;
};

