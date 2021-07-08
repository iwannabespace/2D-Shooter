#include <iostream>
#include <string>
#include "Player.hpp"

void Player::init(sf::RenderWindow* window, const std::string& textBasePath, Coord pos)
{
	this->pos = pos;
	this->window = window;
	this->pos_bul = 0;
	this->score = 0;

	buffer.loadFromFile("Assets/gunshot.ogg"); // load the gunshot.ogg file
	sound.setBuffer(buffer); // set the buffer

	for (int i = 0; i < 14; i++)
		textures[i].loadFromFile(std::string(textBasePath + "soldier" + std::to_string(i) + ".png"));
	
	sprite.setTexture(textures[0]);
	sprite.setPosition({ this->pos.x, this->pos.y });

	for (int i = 0; i < 500; i++) // for 500 times
	{
		bullets.push_back(std::make_pair(new Bullet(this), false)); // Push to 'bullets' vector a pair of new Bullet object and a boolean of false (False stands for that bullet is not shot)
		bullets[i].first->init(window, std::string(textBasePath + "bullet.png"), { sprite.getPosition().x, sprite.getPosition().y }); // initialize the bullet
		bullets[i].first->setSpeed(5.f); // set the speed of bullet to 5 pixels per frame
	}

	state = 1;

	dir = WalkDirection::Up;
}

void Player::walk(float speed, WalkDirection dir, Barrel* barrels, Sandbag* sandbags, int nb, int ns)
{
	this->dir = dir;

	switch (this->dir)
	{
	case WalkDirection::Up:	
		if (state != 1) // This if avoids setting sprite a texture constantly
		{
			sprite.setTexture(textures[0]);
			state = 1;
		}

		if (!checkCollision(dir, barrels, sandbags, nb, ns)) // If no collision
			if (sprite.getPosition().y > 0.f)
				setPosition({ pos.x, pos.y - speed }); // go up

		break;

	case WalkDirection::Down:
		if (state != 2)
		{
			sprite.setTexture(textures[4]);
			state = 2;
		}

		if (!checkCollision(dir, barrels, sandbags, nb, ns))
			if (sprite.getPosition().y + sprite.getGlobalBounds().height < window->getSize().y)
				setPosition({ pos.x, pos.y + speed }); // go down

		break;

	case WalkDirection::Left:
		if (state != 3)
		{
			sprite.setTexture(textures[6]);
			state = 3;
		}

		if (!checkCollision(dir, barrels, sandbags, nb, ns))
			if (sprite.getPosition().x > 0.f)
				setPosition({ pos.x - speed, pos.y }); // go left

		break;

	case WalkDirection::Right:
		if (state != 4)
		{
			sprite.setTexture(textures[2]);
			state = 4;
		}

		if (!checkCollision(dir, barrels, sandbags, nb, ns))
			if (sprite.getPosition().x + sprite.getGlobalBounds().width < window->getSize().x)
				setPosition({ pos.x + speed, pos.y }); // go right

		break;	
	}
}

bool Player::checkCollision(WalkDirection dir, const Barrel* barrels, const Sandbag* sandbags, int nb, int ns)
{
	this->dir = dir;

	switch (this->dir)
	{
	case WalkDirection::Up:
		for (int i = 0; i < nb; i++) // Loop through all barrels
			if (barrels[i].getVisible()) // if barrel is visible
				if (barrels[i].getBarrel().getGlobalBounds().intersects(sprite.getGlobalBounds())) // If any barrel collides with player
					if (barrels[i].getPosition().y < pos.y) // and if player is facing the barrel
						return true; // return true (means there is collision)

		for (int i = 0; i < ns; i++)
			if (sandbags[i].getSandbag().getGlobalBounds().intersects(sprite.getGlobalBounds()))
				if (sandbags[i].getPosition().y < pos.y)
					return true;

		return false;

	case WalkDirection::Down:
		for (int i = 0; i < nb; i++)
			if (barrels[i].getVisible())
				if (barrels[i].getBarrel().getGlobalBounds().intersects(sprite.getGlobalBounds()))
					if (barrels[i].getPosition().y > pos.y)
						return true;

		for (int i = 0; i < ns; i++)
			if (sandbags[i].getSandbag().getGlobalBounds().intersects(sprite.getGlobalBounds()))
				if (sandbags[i].getPosition().y > pos.y)
					return true;

		return false;

	case WalkDirection::Left:
		for (int i = 0; i < nb; i++)
			if (barrels[i].getVisible())
				if (barrels[i].getBarrel().getGlobalBounds().intersects(sprite.getGlobalBounds()))
					if (barrels[i].getPosition().x < pos.x)
						return true;

		for (int i = 0; i < ns; i++)
			if (sandbags[i].getSandbag().getGlobalBounds().intersects(sprite.getGlobalBounds()))
				if (sandbags[i].getPosition().x < pos.x)
					return true;

		return false;

	case WalkDirection::Right:
		for (int i = 0; i < nb; i++)
			if (barrels[i].getVisible())
				if (barrels[i].getBarrel().getGlobalBounds().intersects(sprite.getGlobalBounds()))
					if (barrels[i].getPosition().x > pos.x)
						return true;

		for (int i = 0; i < ns; i++)
			if (sandbags[i].getSandbag().getGlobalBounds().intersects(sprite.getGlobalBounds()))
				if (sandbags[i].getPosition().x > pos.x)
					return true;

		return false;
	}
}

void Player::setPosition(Coord pos)
{
	this->pos = pos;

	sprite.setPosition({ this->pos.x, this->pos.y });
}

void Player::shoot(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(key)) // if the given key is pressed
	{
		bullets[pos_bul].second = true; // set the momentary bullet object to true

		sound.play(); // play the gun shot sound

		switch (dir) // for the direction that the player is orienting
		{
		case WalkDirection::Up: // if is up
			bullets[pos_bul].first->setDirection(dir); // set Bullet's direction to up
			bullets[pos_bul].first->setPosition({ sprite.getPosition().x + 62.f, sprite.getPosition().y + 15.f }); // set Bullet's position to in front of the player's gun
			bullets[pos_bul++].first->getSprite().setRotation(180); // rotate Bullet 180 degrees
			break;
		case WalkDirection::Down:
			bullets[pos_bul].first->setDirection(dir);
			bullets[pos_bul].first->setPosition({ sprite.getPosition().x + 29.f, sprite.getPosition().y + 100.f});
			bullets[pos_bul++].first->getSprite().setRotation(360);
			break;
		case WalkDirection::Left:
			bullets[pos_bul].first->setDirection(dir);
			bullets[pos_bul].first->setPosition({ sprite.getPosition().x - 28.f, sprite.getPosition().y + 40.f });
			bullets[pos_bul++].first->getSprite().setRotation(270);
			break;
		case WalkDirection::Right:
			bullets[pos_bul].first->setDirection(dir);
			bullets[pos_bul].first->setPosition({ sprite.getPosition().x + 100.f, sprite.getPosition().y + 77.f });
			bullets[pos_bul++].first->getSprite().setRotation(270);
			break;
		}

		if (pos_bul == 500) // if the index is 500
			pos_bul = 0; // set it back to 0 so that bullets can be used again
	}
}

Coord Player::getPosition() const
{
	return pos;
}

void Player::setScore(int score)
{
	this->score = score;
}

WalkDirection Player::getDirection() const
{
	return dir;
}

void Player::paint() const
{
	window->draw(sprite);

	for (std::pair<Bullet*, bool> pair : bullets) // Loop through bullets
		if (pair.second) // if the bullet is set to true
			pair.first->paint(); // the paint it
}

void Player::updateBullet(Player* player, Sandbag* sandbags, Barrel* barrels, int ns, int nb)
{
	for (std::pair<Bullet*, bool>& bullet : bullets) // Loop through all the bullets
		if (bullet.second) // if the bullet is set to true
		{
			switch (bullet.first->getDirection()) // if the bullet's direction is 
			{
			case WalkDirection::Up: // up
				for (int i = 0; i < nb; i++) // loop through all the barrels on the screen
					if (barrels[i].getVisible()) // if the current barrel is visible (Not hit from a bullet)
						if (barrels[i].getBarrel().getGlobalBounds().contains(bullet.first->getSprite().getPosition())) // and if the barrel gets hit from a bullet
						{
							barrels[i].setVisible(false); // set it invisible
							bullet.second = false; // set bullet false so that it won't be drawn on the screen
						}

				for (int i = 0; i < ns; i++) // Loop through all the sandbags
					if (sandbags[i].getSandbag().getGlobalBounds().contains(bullet.first->getSprite().getPosition())) // if the sandbag gets hit from a bullet
						bullet.second = false; // set bullet false so that it won't be drawn on the screen

				if (player->getPlayer().getGlobalBounds().contains(bullet.first->getSprite().getPosition())) // if the player gets hit from a bullet
				{
					score++; // increase the score by one
					player->setPosition({ (float)(std::rand() % (int)(window->getSize().x - player->getPlayer().getGlobalBounds().width)),
						(float)(std::rand() % (int)window->getSize().y - player->getPlayer().getGlobalBounds().height) }); // set the player's position to a random position within the screen
					bullet.second = false; // Doesn't work for a reason i don't understand -it is meant to remove bullet from screen-
				}

				if (bullet.first->getSprite().getPosition().y > 0.f) // if the bullet is inside the window
					bullet.first->update(); // update the bullet

				else // if not
					bullet.second = false; // remove the bullet from the screen
				break;
			case WalkDirection::Down:
				for (int i = 0; i < nb; i++)
					if (barrels[i].getVisible())
						if (barrels[i].getBarrel().getGlobalBounds().contains(bullet.first->getSprite().getPosition()))
						{
							barrels[i].setVisible(false);
							bullet.second = false;
						}

				for (int i = 0; i < ns; i++)
					if (sandbags[i].getSandbag().getGlobalBounds().contains(bullet.first->getSprite().getPosition()))
						bullet.second = false;

				if (player->getPlayer().getGlobalBounds().contains(bullet.first->getSprite().getPosition()))
				{
					score++;
					player->setPosition({ (float)(std::rand() % (int)(window->getSize().x - player->getPlayer().getGlobalBounds().width)), 
						(float)(std::rand() % (int)window->getSize().y - player->getPlayer().getGlobalBounds().height) });
					bullet.second = false;
				}

				if (bullet.first->getSprite().getPosition().y < window->getSize().y)
					bullet.first->update();

				else
					bullet.second = false;
				break;
			case WalkDirection::Left:
				for (int i = 0; i < nb; i++)
					if (barrels[i].getVisible())
						if (barrels[i].getBarrel().getGlobalBounds().contains(bullet.first->getSprite().getPosition()))
						{
							barrels[i].setVisible(false);
							bullet.second = false;
						}

				for (int i = 0; i < ns; i++)
					if (sandbags[i].getSandbag().getGlobalBounds().contains(bullet.first->getSprite().getPosition()))
						bullet.second = false;

				if (player->getPlayer().getGlobalBounds().contains(bullet.first->getSprite().getPosition()))
				{
					score++;
					player->setPosition({ (float)(std::rand() % (int)(window->getSize().x - player->getPlayer().getGlobalBounds().width)),
						(float)(std::rand() % (int)window->getSize().y - player->getPlayer().getGlobalBounds().height) });
					bullet.second = false;
				}

				if (bullet.first->getSprite().getPosition().x > 0.f)
					bullet.first->update();

				else
					bullet.second = false;
				break;
			case WalkDirection::Right:
				for (int i = 0; i < nb; i++)
					if (barrels[i].getVisible())
						if (barrels[i].getBarrel().getGlobalBounds().contains(bullet.first->getSprite().getPosition()))
						{
							barrels[i].setVisible(false);
							bullet.second = false;
						}

				for (int i = 0; i < ns; i++)
					if (sandbags[i].getSandbag().getGlobalBounds().contains(bullet.first->getSprite().getPosition()))
						bullet.second = false;

				if (player->getPlayer().getGlobalBounds().contains(bullet.first->getSprite().getPosition()))
				{
					score++;
					player->setPosition({ (float)(std::rand() % (int)(window->getSize().x - player->getPlayer().getGlobalBounds().width)),
						(float)(std::rand() % (int)window->getSize().y - player->getPlayer().getGlobalBounds().height) });
					bullet.second = false;
				}

				if (bullet.first->getSprite().getPosition().x < window->getSize().x)
					bullet.first->update();

				else
					bullet.second = false;
				break;
			}
		}
}

sf::Sprite Player::getPlayer() const
{
	return sprite;
}

int Player::getScore() const
{
	return score;
}