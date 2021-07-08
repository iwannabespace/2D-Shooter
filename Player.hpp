#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <filesystem>
#include "Object.hpp"
#include "Barrel.hpp"
#include "Sandbag.hpp"
#include "Coord.hpp"
#include "Bullet.hpp"

class Bullet;

enum class WalkDirection
{
	Up,
	Down,
	Left,
	Right
};

class Player : public Object // publicly inherits from 'Object' class
{
private:
	sf::Sound sound; // sf::Sound is used for playing sound files that are short in time (sf::Music is for the long one). Using this one because i have a gun shot sound.
	sf::SoundBuffer buffer; // sf::SoundBuffer is loading the sound.
private:
	sf::Texture textures[14];
	int state, pos_bul;
	int score;
	WalkDirection dir;
	std::vector<std::pair<Bullet*, bool>> bullets; // This vector is for storing the Bullet objects, second data type -bool- of std::pair will be used to check if the bullet is on the screen
public:
	void init(sf::RenderWindow* window, const std::string& textBasePath, Coord pos) override;
	void walk(float speed, WalkDirection dir, Barrel* barrels, Sandbag* sandbags, int nb, int ns);
	bool checkCollision(WalkDirection dir, const Barrel* barrels, const Sandbag* sandbags, int nb, int ns); // Added 'WalkDirection dir' because i also want to check which direction player looks to 
	void setPosition(Coord pos);
	void shoot(sf::Keyboard::Key key); // if the given key is pressed then the momentary Bullet element will be set to true which then will get to be printed on the screen.
	Coord getPosition() const;
	void setScore(int score);
	void paint() const override;
	void updateBullet(Player* player, Sandbag* sandbags, Barrel* barrels, int ns, int nb);
	WalkDirection getDirection() const;
	sf::Sprite getPlayer() const; // Returns the sprite of Player
	int getScore() const;
};