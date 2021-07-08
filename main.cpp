#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Game.hpp"

int main()
{
	std::srand(std::time(0));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1050, 700), "2D Shooter", sf::Style::Default, settings);
	window.setFramerateLimit(100); // Set upper fps limit to 100

	Game game(&window, 2.5f, window.getSize().x, window.getSize().y, 3, 5, 2);

	sf::Font font;
	font.loadFromFile("Assets/font.ttf");

	sf::Text text, score_player1, score_player2;
	text.setFont(font);
	score_player1.setFont(font);
	score_player2.setFont(font);
	score_player1.setCharacterSize(12);
	score_player2.setCharacterSize(12);
	score_player1.setPosition({ 0.f, 0.f });
	score_player2.setPosition({ 0.f, 15.f });

	while (window.isOpen())
	{
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}

			if (game.playerOneScore() < 10 && game.playerTwoScore() < 10)
				game.bulletEvent();
		}
		
		score_player1.setString("P1: " + std::to_string(game.playerOneScore()));
		score_player2.setString("P2: " + std::to_string(game.playerTwoScore()));

		if (game.playerOneScore() >= 10)
		{
			text.setString("Player 1 wins, start over? (Y/N)");

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
			{
				game.setPlayerOneScore(0);
				game.setPlayerTwoScore(0);
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				window.close();
		}

		if (game.playerTwoScore() >= 10)
		{
			text.setString("Player 2 wins, start over? (Y/N)");

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
			{
				game.setPlayerOneScore(0);
				game.setPlayerTwoScore(0);
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				window.close();
		}
			

		window.clear();
		if (game.playerOneScore() < 10 && game.playerTwoScore() < 10)
		{
			game.drawBackground();
			game.update();
			window.draw(score_player1);
			window.draw(score_player2);
		}
		else
			window.draw(text);
		window.display();
	}

	return 0;
}