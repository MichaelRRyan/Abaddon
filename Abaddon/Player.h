// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
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
	float collisionRadius; // The collision radius for use in collision detection
	int movementLockTimer; // The time remaining until the player can move again

	int wallMovementLockTime; // How long the movement will be locked after hitting the wall
	float wallLaunchSpeed; // How fast you'll be launched away from the wall if you touch it

	bool active;

	sf::SoundBuffer hurtSoundBuffer;
	sf::Sound hurtSound;


public:
	// Public function members
	Player();
	void setup();
	void loadFiles();

	inline sf::Vector2f getPosition() { return body.getPosition(); } // Return the position of the object
	inline sf::Sprite getBody() { return body; } // Return the body of the player
	int getHealth() { return health; } // return the health of the player
	bool getActive() { return active; } // Return the active state
	float getCollisionRadius() { return collisionRadius; } // Return the collision radius

	void moveUp() { moveDir.y = -1.0f; } // Move the player up
	void moveDown() { moveDir.y = 1.0f; } // Move the player down
	void moveLeft() { moveDir.x = -1.0f; } // Move the player left
	void moveRight() { moveDir.x = 1.0f; } // Move the player right

	void update();
	void die();
	void wallCollisions();
	void damage(int t_damageValue, int t_freezeTime);

	void draw(sf::RenderWindow & t_window);
};

