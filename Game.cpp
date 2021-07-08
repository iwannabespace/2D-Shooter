#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.hpp"

Game::Game(sf::RenderWindow* window, float speed, int w, int h, int nb, int ns, int np)
	: window(window), speed(speed), width(w), height(h), numBarrels(nb), numSandbags(ns), numPlayers(np)
{
	sf::Vector2f bgPos = { 0.0f, 0.0f };

	bgTexture.loadFromFile("Assets/grass.png");
	bgSprite = new sf::Sprite[(width / 350) * (height / 350)];
	
	for (int i = 0; i < (width / 350) * (height / 350); i++)
		bgSprite[i].setTexture(bgTexture);

	for (int i = 0; i < (width / 350); i++)
	{
		bgSprite[i].setPosition(bgPos);
		bgPos.x += 350.0f;
	}

	bgPos = { 0.0f, 350.0f };

	for (int i = (width / 350); i < (width / 350) * (height / 350); i++)
	{
		bgSprite[i].setPosition(bgPos);
		bgPos.x += 350.0f;
	}

	barrel = new Barrel[numBarrels];
	sandbag = new Sandbag[numSandbags];
	player = new Player[numPlayers];

	for (int i = 0; i < numBarrels; i++)
		barrel[i].init(window, "Assets/barrel.png", { (float)(std::rand() % (int)(w - barrel[i].getBarrel().getGlobalBounds().width)), (float)(std::rand() % (int)(h - barrel[i].getBarrel().getGlobalBounds().height)) }); // (int)(w - barrel[i].getBarrel().getGlobalBounds().width)), i am subtracting the width of barrel sprite because i don't want left or right part of barrel to be out of window same goes for y position
	
	for (int i = 0; i < numSandbags; i++)
		sandbag[i].init(window, "Assets/bags.png", { (float)(std::rand() % (int)(w - sandbag[i].getSandbag().getGlobalBounds().width)), (float)(std::rand() % (int)(h - sandbag[i].getSandbag().getGlobalBounds().height)) });
	
	for (int i = 0; i < numPlayers; i++)
		player[i].init(window, "Assets/", { (float)(std::rand() % (int)(w - player[i].getPlayer().getGlobalBounds().width)), (float)(std::rand() % (int)(h - player[i].getPlayer().getGlobalBounds().height)) });
}

Game::~Game()
{
	delete[] barrel;
	delete[] sandbag;
	delete[] player;
	delete[] bgSprite;
}

void Game::drawBackground()
{
	for (int i = 0; i < (width / 350) * (height / 350); i++)
		window->draw(bgSprite[i]);
}

void Game::update()
{
	for (int i = 0; i < numBarrels; i++)
		barrel[i].paint();

	for (int i = 0; i < numSandbags; i++)
		sandbag[i].paint();

	for (int i = 0; i < numPlayers; i++)
		player[i].paint();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // if the w key is pressed
		player[0].walk(speed, WalkDirection::Up, barrel, sandbag, numBarrels, numSandbags);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // if the s key is pressed
		player[0].walk(speed, WalkDirection::Down, barrel, sandbag, numBarrels, numSandbags);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // if the a key is pressed
		player[0].walk(speed, WalkDirection::Left, barrel, sandbag, numBarrels, numSandbags);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // if the d key is pressed
		player[0].walk(speed, WalkDirection::Right, barrel, sandbag, numBarrels, numSandbags);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // if the up arrow key is pressed
		player[1].walk(speed, WalkDirection::Up, barrel, sandbag, numBarrels, numSandbags);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // if the down arrow key is pressed
		player[1].walk(speed, WalkDirection::Down, barrel, sandbag, numBarrels, numSandbags);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // if the left arrow key is pressed
		player[1].walk(speed, WalkDirection::Left, barrel, sandbag, numBarrels, numSandbags);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // if the right arrow key is pressed
		player[1].walk(speed, WalkDirection::Right, barrel, sandbag, numBarrels, numSandbags);

	player[0].updateBullet(&player[1], sandbag, barrel, numSandbags, numBarrels);
	player[1].updateBullet(&player[0], sandbag, barrel, numSandbags, numBarrels);
}

void Game::bulletEvent()
{
	player[0].shoot(sf::Keyboard::Space);
	player[1].shoot(sf::Keyboard::Return);
}

void Game::setPlayerOneScore(int score)
{
	player[0].setScore(score);
}

void Game::setPlayerTwoScore(int score)
{
	player[1].setScore(score);
}

int Game::playerOneScore() const
{
	return player[0].getScore();
}

int Game::playerTwoScore() const
{
	return player[1].getScore();;
}