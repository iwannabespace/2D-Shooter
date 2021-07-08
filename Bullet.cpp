#include "Bullet.hpp"

Bullet::Bullet(Player* player)
	: player(player)
{
}

void Bullet::update()
{
	switch (dir) // if the direction that the bullet is orienting
	{
	case WalkDirection::Up: // is up
		if (sprite.getPosition().y > 0.f) // if the bullet's y position is greater than 0.f (which means that bullet is not out of the screen for the upper side)
			move(speed); // move the bullet with the speed member variable
		break;
	case WalkDirection::Down:
		if (sprite.getPosition().y < window->getSize().y)
			move(speed);
		break;
	case WalkDirection::Left:
		if (sprite.getPosition().y > 0.f)
			move(speed);
		break;
	case WalkDirection::Right:
		if (sprite.getPosition().y < window->getSize().x)
			move(speed);
		break;
	}
}

void Bullet::init(sf::RenderWindow* window, const std::string& texturePath, Coord pos)
{
	this->pos = pos;
	this->window = window;
	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);
}

void Bullet::move(float speed)
{
	switch (dir)
	{
	case WalkDirection::Up:
		sprite.move({ 0.f, -speed });
		break;
	case WalkDirection::Down:
		sprite.move({ 0.f, speed });
		break;
	case WalkDirection::Left:
		sprite.move({ -speed, 0.f });
		break;
	case WalkDirection::Right:
		sprite.move({ speed, 0.f });
		break;
	}
}

void Bullet::setSpeed(float speed)
{
	this->speed = speed;
}

void Bullet::setPosition(Coord pos)
{
	this->pos = pos;
	sprite.setPosition({ this->pos.x, this->pos.y });
}

void Bullet::setDirection(WalkDirection dir)
{
	this->dir = dir;
}

void Bullet::paint() const
{
	window->draw(sprite);
}

sf::Sprite& Bullet::getSprite()
{
	return sprite;
}

WalkDirection Bullet::getDirection() const
{
	return dir;
}
