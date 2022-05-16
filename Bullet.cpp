#include "Bullet.h"


Bullet::Bullet() {}

Bullet::Bullet(sf::Vector2f speed)
{
	this->speed = speed;

	instance = sf::CircleShape(bulletRadius, 8);
	instance.setFillColor(sf::Color::Red);
	instance.setOrigin(instance.getRadius(), instance.getRadius());
}

void Bullet::ShootInit(sf::Vector2f startPos)
{
	startPosition = startPos;
	instance.setPosition(startPosition);
	init = true;
}

sf::Vector2f Bullet::getPos()
{
	return instance.getPosition();
}

bool Bullet::Shoot()
{

	if (init && instance.getPosition().y > 0)
	{
		instance.setPosition(instance.getPosition() + speed);
		return true;
	}
	else
		return false;

}

void Bullet::setPosition(float x, float y)
{
	instance.setPosition(x, y);
}

void Bullet::stop()
{
	init = false;
}

sf::FloatRect Bullet::getGlobalBounds()
{
	return instance.getGlobalBounds();
}

sf::CircleShape Bullet::getInstance()
{
	return instance;
}

void Bullet::setVelocity(float speed, sf::Vector2f aimDirNorm)
{
	currVelocity = aimDirNorm * speed;
}

sf::Vector2f Bullet::getPosition()
{
	return instance.getPosition();
}

sf::Vector2f Bullet::getVelocity() 
{
	return currVelocity;
}

float Bullet::getRadius() 
{
	return bulletRadius;
}

void Bullet::bulletRicochet(sf::FloatRect& obstacleBounds, sf::FloatRect& bulletBounds, Bullet& bullet, sf::Vector2f aimDir, sf::Vector2f aimDirNorm, sf::Vector2f ricochetDir)
{
	if (bulletBounds.intersects(obstacleBounds))
	{
		if (bulletBounds.top < obstacleBounds.top
			&& bulletBounds.top + bulletBounds.height < obstacleBounds.top + obstacleBounds.height
			&& bulletBounds.left < obstacleBounds.left + obstacleBounds.width
			&& bulletBounds.left + bulletBounds.width > obstacleBounds.left) {

			sf::Vector2f tempPos(bulletBounds.left, obstacleBounds.top - bulletBounds.height);

			-aimDir = tempPos - ricochetDir;
			aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
			aimDirNorm.x = -aimDirNorm.x;

			bullet.stop();

			bullet.setVelocity(bullet.getSpeed(), -aimDirNorm);
			bullet = Bullet(bullet.getVelocity());
			bullet.ShootInit(tempPos);
		}
		else if (bulletBounds.top > obstacleBounds.top
			&& bulletBounds.top + bulletBounds.height > obstacleBounds.top + obstacleBounds.height
			&& bulletBounds.left < obstacleBounds.left + obstacleBounds.width
			&& bulletBounds.left + bulletBounds.width > obstacleBounds.left) {

			sf::Vector2f tempPos(bulletBounds.left, obstacleBounds.top + obstacleBounds.height);

			-aimDir = tempPos - ricochetDir;
			aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
			aimDirNorm.x = -aimDirNorm.x;

			bullet.stop();

			bullet.setVelocity(bullet.getSpeed(), -aimDirNorm);
			bullet = Bullet(bullet.getVelocity());
			bullet.ShootInit(tempPos);
		}

		if (bulletBounds.left < obstacleBounds.left
			&& bulletBounds.left + bulletBounds.width < obstacleBounds.left + obstacleBounds.width
			&& bulletBounds.top < obstacleBounds.top + obstacleBounds.height
			&& bulletBounds.top + bulletBounds.height > obstacleBounds.top) {

			sf::Vector2f tempPos(obstacleBounds.left - bulletBounds.width, bulletBounds.top);

			-aimDir = tempPos - ricochetDir;
			aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
			aimDirNorm.y = -aimDirNorm.y;

			bullet.stop();

			bullet.setVelocity(bullet.getSpeed(), -aimDirNorm);
			bullet = Bullet(bullet.getVelocity());
			bullet.ShootInit(tempPos);
		}
		else if (bulletBounds.left > obstacleBounds.left
			&& bulletBounds.left + bulletBounds.width > obstacleBounds.left + obstacleBounds.width
			&& bulletBounds.top < obstacleBounds.top + obstacleBounds.height
			&& bulletBounds.top + bulletBounds.height > obstacleBounds.top) {

			sf::Vector2f tempPos(obstacleBounds.left + obstacleBounds.width, bulletBounds.top);

			-aimDir = tempPos - ricochetDir;
			aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
			aimDirNorm.y = -aimDirNorm.y;

			bullet.stop();

			bullet.setVelocity(bullet.getSpeed(), -aimDirNorm);
			bullet = Bullet(bullet.getVelocity());
			bullet.ShootInit(tempPos);
		}

	}
}

