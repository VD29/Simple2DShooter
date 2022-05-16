#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Obstacle.h"


class Bullet
{
public:

	Bullet();

	Bullet(sf::Vector2f);

	void ShootInit(sf::Vector2f);

	sf::Vector2f getPos();

	bool Shoot();

	void setPosition(float, float);

	void stop();

	sf::FloatRect getGlobalBounds();

	sf::CircleShape getInstance();

	void setVelocity(float, sf::Vector2f);

	sf::Vector2f getPosition();

	sf::Vector2f getVelocity();

	void bulletRicochet(sf::FloatRect&, sf::FloatRect&, Bullet&, sf::Vector2f, sf::Vector2f, sf::Vector2f);

	float getRadius();
	float getSpeed() { return bulletSpeed; }

private:
	int init = false;
	float bulletRadius = 5.f;
	float bulletSpeed = 10.f;
	sf::Vector2f currVelocity;
	sf::Vector2f speed, startPosition;
	sf::CircleShape instance;

};
