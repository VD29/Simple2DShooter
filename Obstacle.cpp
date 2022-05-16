#include "Obstacle.h"

Obstacle::Obstacle(sf::Color fillColor, float x, float y)
{
	this->x = x;
	this->y = y;

	instance = sf::RectangleShape(sf::Vector2f(x, y));
	instance.setFillColor(fillColor);

}

void Obstacle::setPosition(float x, float y)
{
	instance.setPosition(x, y);
}

sf::FloatRect Obstacle::getGlobalBounds()
{
	return instance.getGlobalBounds();
}

sf::RectangleShape Obstacle::getInstance()
{
	return instance;
}

sf::Vector2f Obstacle::getPosition()
{
	return instance.getPosition();
}

sf::Vector2f Obstacle::getSize() 
{
	return instance.getSize();
}

void Obstacle::playersCollision(sf::FloatRect& obstacleBounds, sf::FloatRect& playerBounds, Player& player)
{
	if (playerBounds.intersects(obstacleBounds)) {
		//Bottom
		if (playerBounds.top < obstacleBounds.top
			&& playerBounds.top + playerBounds.height < obstacleBounds.top + obstacleBounds.height
			&& playerBounds.left < obstacleBounds.left + obstacleBounds.width
			&& playerBounds.left + playerBounds.width > obstacleBounds.left)
		{
			player.speed.y = 0.f;
			sf::Vector2f temp(playerBounds.left, obstacleBounds.top - playerBounds.height);
			player.setPosition(temp);
		}
		//Top
		else if (playerBounds.top > obstacleBounds.top
			&& playerBounds.top + playerBounds.height > obstacleBounds.top + obstacleBounds.height
			&& playerBounds.left < obstacleBounds.left + obstacleBounds.width
			&& playerBounds.left + playerBounds.width > obstacleBounds.left)
		{
			player.speed.y = 0.f;
			sf::Vector2f temp(playerBounds.left, obstacleBounds.top + obstacleBounds.height);
			player.setPosition(temp);
		}

		//Right
		if (playerBounds.left < obstacleBounds.left
			&& playerBounds.left + playerBounds.width < obstacleBounds.left + obstacleBounds.width
			&& playerBounds.top < obstacleBounds.top + obstacleBounds.height
			&& playerBounds.top + playerBounds.height > obstacleBounds.top)
		{
			player.speed.x = 0.f;
			sf::Vector2f temp(obstacleBounds.left - playerBounds.width, playerBounds.top);
			player.setPosition(temp);
		}
		//Left
		else if (playerBounds.left > obstacleBounds.left
			&& playerBounds.left + playerBounds.width > obstacleBounds.left + obstacleBounds.width
			&& playerBounds.top < obstacleBounds.top + obstacleBounds.height
			&& playerBounds.top + playerBounds.height > obstacleBounds.top)
		{
			player.speed.x = 0.f;
			sf::Vector2f temp(obstacleBounds.left + obstacleBounds.width, playerBounds.top);
			player.setPosition(temp);
		}
	}
}


