#include "Barrel.hpp"

void Barrel::init(sf::RenderWindow* window, const std::string& texturePath, Coord pos)
{
    this->pos = pos;
    this->window = window;
    this->isVisible = true;
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    sprite.setPosition({ this->pos.x, this->pos.y });
}

void Barrel::paint() const
{
    if (isVisible)
        window->draw(sprite);
}

void Barrel::setVisible(bool isVisible)
{
    this->isVisible = isVisible;
}

bool Barrel::getVisible() const
{
    return isVisible;
}

Coord Barrel::getPosition() const
{
    return pos;
}

sf::Sprite Barrel::getBarrel() const
{
    return sprite;
}