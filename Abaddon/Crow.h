// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Globals.h"

class Crow
{
	// Enum for behaviour state
	const enum Behaviour { Standby, Patrol, PrepareToDive, Dive };

	// Declare private data members
	sf::Texture spriteSheet;
	sf::Sprite body;
	sf::Vector2f velocity;
	int health;
	int attackDamage;
	int frameNum; // Frame number used for animating the sprite
	int frameDelay; // The delay between frame change
	float collisionRadius; // The radius used to check crow collisions
	float speed; // How fast the crow moves normally
	float diveSpeed; // How fast the crow moves when diving for the player
	float diveRange; // How close the player has to be along the x axis to the crow for it to dive
	float diveHeight; // How far away the crow has to be along the y axis for the crow to dive
	Behaviour behaviour; // Controls which behaviour is run
	bool active;

	

public:
	// Public function members
	Crow();
	void setup();
	void loadFiles();

	void update(Player & t_player, float & t_score); // Update the crow and pick the behaviour
	void patrol(Player t_player); // Handles the patrol behaviour before the crow attacks
	void dive(Player & t_player); // The attack behaviour handles the crow attacking the player
	void wallCollisions(); // Manage the wall collisions
	void draw(sf::RenderWindow & t_window); // Draw the crow
	void animateSprite();

	// Get functions
	inline sf::Sprite getBody() { return body; } // Get the bodt component of the crow
	inline bool getActive() { return active; } // Get the active state of the crow
	float getCollisionRadius() { return collisionRadius; } // Return the collision radius

	// Set/change functions
	inline void setActive(bool t_active) { active = t_active; } // Set the active state of the object
	inline void changeHealth(int t_changeAmount) { health += t_changeAmount; } // Change the health of the crow by the inputted value
	inline void setPosition(float t_xPos, float t_yPos) { body.setPosition(t_xPos, t_yPos); } // Set the position of the crow using two floats
	inline void setPosition(sf::Vector2f t_position) { body.setPosition(t_position); } // Set the position of the crow using a vector
};

