#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.hpp"
#include "Barrel.hpp"
#include "Sandbag.hpp"
#include "Coord.hpp"

class Game
{
private:
	float speed;
	int numBarrels;
	int numSandbags;
	int numPlayers;
	int width;
	int height;
	sf::RenderWindow* window;
	sf::Texture bgTexture;
	sf::Sprite* bgSprite; // Made this pointer because i want to have more than one background image (because of bg image is 350x350 -smaller than window-)
	Barrel* barrel;
	Sandbag* sandbag;
	Player* player;
public:
	Game(sf::RenderWindow* window, float speed, int w, int h, int nb, int ns, int np); // Added 'sf::RenderWindow* window' because some variables inside the Game class require an sf::RenderWindow
	~Game();
	void drawBackground();
	void update();
	void bulletEvent(); // Handles bullet events for key presses
	void setPlayerOneScore(int score);
	void setPlayerTwoScore(int score);
	int playerOneScore() const;
	int playerTwoScore() const;
};