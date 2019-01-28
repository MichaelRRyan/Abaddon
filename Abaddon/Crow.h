// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "Player.h"

class Crow
{
	// Declare private data members
	sf::Texture spriteSheet;
	sf::Sprite body;
	sf::Vector2f velocity;
	int health;
	float speed;

public:
	// Public function members
	Crow();
	void setup();
	void loadFiles();

	sf::Sprite getBody();

	void update(Player t_player);
	void attack(Player t_player);
};

