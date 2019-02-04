// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "MyVector2.h"
#include "Globals.h"

class Player
{
	// Declare private data members
	sf::Texture spriteSheet;
	sf::Sprite body;
	sf::Vector2f moveDir;
	sf::Vector2f velocity;
	int health;
	float speed;
	float friction;
	int movementLockTimer; // The time remaining until the player can move again

	int wallMovementLockTime; // How long the movement will be locked after hitting the wall
	float wallLaunchSpeed; // How fast you'll be launched away from the wall if you touch it

	bool active;


public:
	// Public function members
	Player();
	void setup();
	void loadFiles();

	sf::Vector2f getPosition();
	sf::Sprite getBody();
	int getHealth();
	bool getActive();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void update();
	void die();
	void wallCollisions();
	void damage(int t_damageValue, int t_freezeTime);

	void draw(sf::RenderWindow & t_window);
};

