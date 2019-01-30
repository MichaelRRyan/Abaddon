// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Globals.h"

class Crow
{
	// Declare private data members
	sf::Texture spriteSheet;
	sf::Sprite body;
	sf::Vector2f velocity;
	int health;
	float speed; // How fast the crow moves normally
	float diveSpeed; // How fast the crow moves when diving for the player
	int behaviour; // Controls which behaviour is run
	float diveRange; // How close the player has to be along the x axis to the crow for it to dive
	float diveHeight; // How far away the crow has to be along the y axis for the crow to dive

public:
	// Public function members
	Crow();
	void setup();
	void loadFiles();

	sf::Sprite getBody();

	void update(Player t_player); // Update the crow and pick the behaviour
	void attack(Player t_player); // The attack behaviour handles the crow attacking the player
	void patrol(Player t_player); // Handles the patrol behaviour before the crow attacks
};

