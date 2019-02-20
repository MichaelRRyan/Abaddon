// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "Globals.h"

const float MAX_SPEED = 8.0f;
const float MIN_SPEED = 3.0f;
const float BASE_SCALE = 0.5f;

class Obstacle
{
	// Private data memebers
	sf::Texture texture; //Texture used for the sprite
	sf::Sprite body; // Sprite used for the body of the object
	sf::Vector2f velocity; // Velocity the object travels at
	int health; // Stores the health of the object
	float speed; // Speed multiplier for the object
	float collisionRadius; // The collision radius for the object for use in collisions
	bool active; // Active state for the object

public:
	Obstacle();
	void loadFiles();
	void respawn();
	void update();
	void draw(sf::RenderWindow & t_window);

	inline void setActive(bool t_active) { active = t_active; } // Set the active state of the object

	sf::Sprite getBody();
	inline bool getActive() { return active; } // Return the active state of the object
	inline sf::Vector2f getPosition() { return body.getPosition(); } // Return the position of the object
	inline float getCollisionRadius() { return collisionRadius; } // Return the collision radius of the object
};

