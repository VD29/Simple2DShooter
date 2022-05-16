#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Obstacle
{
public:
	Obstacle(sf::Color, float, float);
	void setPosition(float, float);

	sf::FloatRect getGlobalBounds();

	sf::RectangleShape getInstance();

	sf::Vector2f getPosition();
	sf::Vector2f getSize();

	void playersCollision(sf::FloatRect&, sf::FloatRect&, Player&);
	

private:
	
	float x, y;
	sf::RectangleShape instance;
};
