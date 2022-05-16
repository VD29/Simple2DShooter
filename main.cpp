#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "math.h"

#include "Player.h"
#include "Bullet.h"
#include "Obstacle.h"

using namespace std;
using namespace sf;

const int width = 768, height = 800;

int playerFireRate = 30;
int playerNextFire = playerFireRate;

int enemyFireRate = 30;
int enemyNextFire = enemyFireRate;

int scorePlayer = 0;
int scoreEnemy = 0;

int main()
{
	RenderWindow app(VideoMode(width, height), "Simple Shooter");
	app.setFramerateLimit(60);

	vector<Bullet> enemyBullets;
	vector<Bullet> playerBullets;

	Player player(Color::White);
	Player enemy(Color::Magenta);

	Font mainFont;
	Text gameDoneMsg = Text("", mainFont);
	Text scorePlayerText = Text("PLAYER SCORE/0", mainFont);
	Text scoreEnemyText = Text("ENEMY SCORE/0", mainFont);
	Text healthText = Text("HEALTH/MAX", mainFont);

	//----GameObject Settings
	player.setPosMiddleOfXAndSetY(width, height - 100);
	enemy.setPosMiddleOfXAndSetY(width, height - 700);

	if (!mainFont.loadFromFile("resources/sansation.ttf")) return -1;
	scorePlayerText.setFillColor(Color::Black);
	scoreEnemyText.setFillColor(Color::Black);
	healthText.setFillColor(Color::Black);
	gameDoneMsg.setFillColor(Color::Red);

	scorePlayerText.setPosition(width / 2 - scorePlayerText.getLocalBounds().width / 2, 0);
	scoreEnemyText.setPosition(width / 2 - scoreEnemyText.getLocalBounds().width / 2, 30);
	healthText.setPosition(width / 2 - healthText.getLocalBounds().width / 2, height - 50);
	gameDoneMsg.setPosition(width / 2 - gameDoneMsg.getLocalBounds().width / 2, height / 2 - gameDoneMsg.getLocalBounds().height / 2);

	while (app.isOpen())
	{
		Event event;
		if (app.pollEvent(event))
		{
			if (event.type == Event::EventType::Closed)
				app.close();
		}

		Vector2f mousePosWindow(Mouse::getPosition(app));
		Vector2f aimDir, aimDirAI;
		Vector2f aimDirNorm, aimDirNormAI;
		aimDir = mousePosWindow - player.getPosition();
		aimDirAI = player.getPosition() - enemy.getPosition();
		aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
		aimDirNormAI = aimDirAI / sqrt(pow(aimDirAI.x, 2) + pow(aimDirAI.y, 2));
		

		//Create obstacles
		Obstacle obstacle1(Color::Black, 50, 300);
		Obstacle obstacle2(Color::Black, 200, 50);
		Obstacle obstacle3(Color::Black, 50, 300);
		obstacle1.setPosition(40, 220);
		obstacle2.setPosition(280, 350);
		obstacle3.setPosition(680, 220);

		FloatRect obstacle1Bounds = obstacle1.getGlobalBounds();
		FloatRect obstacle2Bounds = obstacle2.getGlobalBounds();
		FloatRect obstacle3Bounds = obstacle3.getGlobalBounds();


		//Move Actors
		if (!player.IsDie())
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::W))
				player.speed.y = -player.getSpeed();

			if (Keyboard::isKeyPressed(Keyboard::Key::S))
				player.speed.y = player.getSpeed();

			if (Keyboard::isKeyPressed(Keyboard::Key::D))
				player.speed.x = player.getSpeed();

			if (Keyboard::isKeyPressed(Keyboard::Key::A))
				player.speed.x = -player.getSpeed();

			player.move(player.speed);
			player.speed = { 0.f, 0.f };
		}

		if (!enemy.IsDie())
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
				enemy.speed.y = -enemy.getSpeed();

			if (Keyboard::isKeyPressed(Keyboard::Key::Down))
				enemy.speed.y = enemy.getSpeed();

			if (Keyboard::isKeyPressed(Keyboard::Key::Left))
				enemy.speed.x = -enemy.getSpeed();

			if (Keyboard::isKeyPressed(Keyboard::Key::Right))
				enemy.speed.x = enemy.getSpeed();

			enemy.move(enemy.speed);
			enemy.speed = { 0.f, 0.f };
		}

		if (playerNextFire < playerFireRate)
			playerNextFire++;
		if (enemyNextFire < enemyFireRate)
			enemyNextFire++;

		//Shoot trigger
		Vector2f ricochet2Dir;
		if (!player.IsDie() && Mouse::isButtonPressed(Mouse::Left) && playerNextFire >= playerFireRate)
		{
			playerNextFire = 0;
			Bullet playerBullet;
			playerBullet.setVelocity(playerBullet.getSpeed(), aimDirNorm);
			playerBullet = Bullet(playerBullet.getVelocity());
			ricochet2Dir = player.getPosition();
			playerBullet.ShootInit(player.getPosition());
			playerBullets.push_back(playerBullet);
		}

		Vector2f ricochetDir;
		if (!enemy.IsDie() && Keyboard::isKeyPressed(Keyboard::Key::Space) && enemyNextFire >= enemyFireRate)
		{
			enemyNextFire = 0;
			Bullet enemyBullet;
			enemyBullet.setVelocity(enemyBullet.getSpeed(), aimDirNormAI);
			enemyBullet = Bullet(enemyBullet.getVelocity());
			ricochetDir = enemy.getPosition();
			enemyBullet.ShootInit(enemy.getPosition());
			enemyBullets.push_back(enemyBullet);
		}

		//Shoot bullets
		for (int i = 0; i < playerBullets.size(); i++)
		{
			if (!playerBullets[i].Shoot())
			{
				playerBullets.erase(playerBullets.begin() + i);
			}
		}

		for (int i = 0; i < enemyBullets.size(); i++)
		{
			if (!enemyBullets[i].Shoot())
			{
				enemyBullets.erase(enemyBullets.begin() + i);
			}
		}

		//Bullet Collision
		for (int i = 0; i < enemyBullets.size(); i++)
		{
			FloatRect enemyBulletBounds = enemyBullets[i].getGlobalBounds();
			
			if (enemyBulletBounds.intersects(player.getGlobalBounds()))
			{
				enemyBullets[i].stop();

				if (!player.IsDie())
				{
					player.Hurt();

					scoreEnemy++;

					player.setPosMiddleOfXAndSetY(width, height - 100);
					enemy.setPosMiddleOfXAndSetY(width, height - 700);
				}
			}

			//Enemy bullet Ricochets
			enemyBullets[i].bulletRicochet(obstacle1Bounds, enemyBulletBounds, enemyBullets[i], aimDirAI, aimDirNormAI, ricochetDir);
			enemyBullets[i].bulletRicochet(obstacle2Bounds, enemyBulletBounds, enemyBullets[i], aimDirAI, aimDirNormAI, ricochetDir);
			enemyBullets[i].bulletRicochet(obstacle3Bounds, enemyBulletBounds, enemyBullets[i], aimDirAI, aimDirNormAI, ricochetDir);
		}

		for (int i = 0; i < playerBullets.size(); i++)
		{
			FloatRect playerBulletBounds = playerBullets[i].getGlobalBounds();

			if (playerBulletBounds.intersects(enemy.getGlobalBounds()))
			{
				playerBullets[i].stop();

				if (!enemy.IsDie())
				{
					enemy.Hurt();

					scorePlayer++;

					player.setPosMiddleOfXAndSetY(width, height - 100);
					enemy.setPosMiddleOfXAndSetY(width, height - 700);
				}
			}

			//Player bullet Ricochets
			playerBullets[i].bulletRicochet(obstacle1Bounds, playerBulletBounds, playerBullets[i], aimDir, aimDirNorm, ricochet2Dir);
			playerBullets[i].bulletRicochet(obstacle2Bounds, playerBulletBounds, playerBullets[i], aimDir, aimDirNorm, ricochet2Dir);
			playerBullets[i].bulletRicochet(obstacle3Bounds, playerBulletBounds, playerBullets[i], aimDir, aimDirNorm, ricochet2Dir);
		}

		//Player&Enemy Teleportation
		player.worldTeleportation(player);
		enemy.worldTeleportation(enemy);

		//Player & Enemy Collisions with obstacles
		FloatRect playerBounds = player.getGlobalBounds();
		FloatRect enemyBounds = enemy.getGlobalBounds();

		obstacle1.playersCollision(obstacle1Bounds, playerBounds, player);
		obstacle2.playersCollision(obstacle2Bounds, playerBounds, player);
		obstacle3.playersCollision(obstacle3Bounds, playerBounds, player);
		obstacle1.playersCollision(obstacle1Bounds, enemyBounds, enemy);
		obstacle2.playersCollision(obstacle2Bounds, enemyBounds, enemy);
		obstacle3.playersCollision(obstacle3Bounds, enemyBounds, enemy);

		app.clear(Color::Color(217, 217, 217));

		//Draw bullets
		for (int i = 0; i < playerBullets.size(); i++)
			app.draw(playerBullets[i].getInstance());

		for (int i = 0; i < enemyBullets.size(); i++)
			app.draw(enemyBullets[i].getInstance());

		//Draw players
		app.draw(player.getInstance());
		app.draw(enemy.getInstance());

		//Draw obstacles
		app.draw(obstacle1.getInstance());
		app.draw(obstacle2.getInstance());
		app.draw(obstacle3.getInstance());

		healthText.setString("HEALTH: " + to_string(player.getHealth()));
		scorePlayerText.setString("PLAYER SCORE: " + to_string(scorePlayer));
		scoreEnemyText.setString("ENEMY SCORE: " + to_string(scoreEnemy));

		//Draw UIs
		app.draw(scorePlayerText);
		app.draw(scoreEnemyText);
		app.draw(healthText);
		if (player.IsDie()) app.draw(gameDoneMsg);

		app.display();
	}

	return 0;
}
