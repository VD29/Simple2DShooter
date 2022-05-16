#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player() {}
	Player(sf::Color);
	void setPosMiddleOfXAndSetY(float, float);
	void move(sf::Vector2f);
	void setPosition(sf::Vector2f);
	bool Hurt();
	bool IsDie();
	int getHealth();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();
	sf::RectangleShape getInstance();
	sf::Vector2f getSize();
	void worldTeleportation(Player&);
	int getSpeed() { return instanceSpeed; }

	sf::Vector2f speed = { 0.0f, 0.0f };
	const int MAX_HEALTH = 10;

private:
	const int width = 768, height = 800;
	int instanceSpeed = 5;
	int isDie = false;
	int health = MAX_HEALTH;
	const sf::Vector2f size{30,30};
	const int damage = 1;
	sf::RectangleShape instance;
	
};

