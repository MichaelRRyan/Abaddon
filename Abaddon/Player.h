// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "MyVector2.h"

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


public:
	Player();
	void setup();
	void loadFiles();

	sf::Sprite getBody();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void update();
};

