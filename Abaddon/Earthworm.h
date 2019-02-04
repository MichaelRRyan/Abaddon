// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "Globals.h"

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
	float gravityModifier;

public:
	Earthworm();
	void setupShapes();
	void spawn();

	void update();
	void moveTail();
	void checkGameBounds();
	void draw(sf::RenderWindow & t_window);

	inline bool getActive() { return active; }
};

