// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Audio.hpp>
#include <iostream>
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

	sf::SoundBuffer gunshotSoundBuffer; // Sound buffer for the gunshot
	sf::Sound gunshotSound; // Sound for the gunshot

public:
	Gun();
	void setupSounds(); // Load and setup sound files
	void fireBullet(sf::Vector2f t_position, sf::Vector2f t_target, int & t_screenShakeTimer);
	void updateBullets(Crow t_crows[], int t_maxCrows ,Earthworm t_eartworms[], int t_maxEarthworms);
	void checkBulletCollisions(Bullet & t_bullet, Crow t_crows[], int t_maxCrows, Earthworm t_eartworms[], int t_maxEarthworms);
	void drawBullets(sf::RenderWindow & t_window);
	Bullet getBullet(int t_num);
	inline int getNumberOfBullets() { return MAX_BULLETS; }
	
};

