// @Author Michael Rainsford Ryan
#pragma once

#include "Bullet.h"
#include "MyVector2.h"
#include "Crow.h"
#include "Earthworm.h"

class Gun
{
	// Private data memebers
	static const int MAX_BULLETS{ 10 };
	Bullet bullets[MAX_BULLETS];
	float speed;
	int damage;
	int coolDown; // The cooldown everytime a bullet is fired
	int coolDownTimer; // The current cooldown until another bullet can be fired

public:
	Gun();
	void fireBullet(sf::Vector2f t_position, sf::Vector2f t_target);
	void updateBullets(Crow & t_crow, Earthworm & t_eartworm);
	void checkBulletCollisions(Bullet & t_bullet, Crow & t_crow, Earthworm & t_eartworm);
	void drawBullets(sf::RenderWindow & t_window);
	Bullet getBullet(int t_num);
	inline int getNumberOfBullets() { return MAX_BULLETS; }
};

