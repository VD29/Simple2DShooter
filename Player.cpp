#include "Player.h"

Player::Player(sf::Color fillColor)
{
	instance.setSize(size);
	instance.setFillColor(fillColor);
	instance.setOrigin(instance.getScale().x/2, instance.getScale().y / 2);
}

void Player::setPosMiddleOfXAndSetY(float width, float y)
{
	instance.setPosition(width / 2, y);
}

void Player::move(sf::Vector2f speed)
{
	this->speed = speed;
	setPosition(instance.getPosition() + speed);
}

void Player::setPosition(sf::Vector2f pos)
{
	instance.setPosition(pos);
}

bool Player::Hurt()
{
	health -= damage;

	if (health == 0)
	{
		health = 0;
		isDie = true;

		return false;
	}

	return true;
}

bool Player::IsDie()
{
	return isDie;
}

int Player::getHealth()
{
	return health;
}

sf::FloatRect Player::getGlobalBounds()
{
	return instance.getGlobalBounds();
}

sf::Vector2f Player::getPosition()
{
	return instance.getPosition();
}

sf::RectangleShape Player::getInstance()
{
	return instance;
}

sf::Vector2f Player::getSize() 
{
	return instance.getScale();
}

void Player::worldTeleportation(Player& instance)
{
	if (instance.getPosition().x <= 0) { //Left
		sf::Vector2f temp(width + instance.getPosition().x, instance.getPosition().y);
		instance.setPosition(temp);
	}
	if (instance.getPosition().y <= 0) { //Top
		sf::Vector2f temp(instance.getPosition().x, height + instance.getPosition().y);
		instance.setPosition(temp);
	}
	if (instance.getPosition().x >= width) { //Right
		sf::Vector2f temp(width - instance.getPosition().x, instance.getPosition().y);
		instance.setPosition(temp);
	}
	if (instance.getPosition().y >= height) { //Bottom
		sf::Vector2f temp(instance.getPosition().x, height - instance.getPosition().y);
		instance.setPosition(temp);
	}
}
