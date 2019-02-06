// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Player.h"

class Earthworm
{
	static const int TAIL_LENGTH{ 10 };
	sf::CircleShape head;
	sf::CircleShape tail[TAIL_LENGTH];
	sf::Vector2f velocity;
	int health;
	float speed;
	float tailRadius; // The radius of the tail
	float headRadius; // The radius of the head
	float tailDistanceModifier; // The distance removed from the radius to find the distance between tail segments
	bool active;
	bool inWall;
	float gravityModifier;

public:
	Earthworm();
	void setupShapes();
	void spawn();

	void jumpAttack();

	void update(Player & t_player);
	void moveTail();
	void checkGameBounds();
	void playerCollisions(Player & t_player);
	bool isColliding(sf::Sprite t_collider);
	void draw(sf::RenderWindow & t_window);

	inline bool getActive() { return active; }
	inline void changeHealth(int t_changeAmount) { health += t_changeAmount; } // Change the health of the crow by the inputted value
};

