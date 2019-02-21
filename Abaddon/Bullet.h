// @Author Michael Rainsford Ryan
#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"

class Bullet
{
	// Declare private data members
	sf::Texture spriteTexture;
	sf::Sprite body;
	sf::Vector2f velocity;
	float speed;
	float collisionRadius;
	bool active;
	int damage;

public:
	Bullet();
	void loadFiles();

	int getDamage();
	sf::Sprite getBody();
	bool getActive();
	inline float getCollisionRadius() { return collisionRadius; } // Return the collision radius
	inline sf::Vector2f getPosition() { return body.getPosition(); } // Returns the position of the bullet
	void setActive(bool t_active);

	void intialise(sf::Vector2f t_position, sf::Vector2f t_direction, float t_speed, int t_damage);
	bool isColliding(sf::Sprite t_collider);
	void update();

	void draw(sf::RenderWindow & t_window);
};

