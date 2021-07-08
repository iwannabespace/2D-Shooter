#include "Sandbag.hpp"

void Sandbag::init(sf::RenderWindow* window, const std::string& texturePath, Coord pos)
{
    this->pos = pos;
    this->window = window;
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    sprite.setPosition({ this->pos.x, this->pos.y });
}

void Sandbag::paint() const
{
    window->draw(sprite);
}

Coord Sandbag::getPosition() const
{
    return pos;
}

sf::Sprite Sandbag::getSandbag() const
{
    return sprite;
}