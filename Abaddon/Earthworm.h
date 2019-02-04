// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>

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

public:
	Earthworm();
	void setup();
	void setupShapes();

	void update(sf::RenderWindow & t_window);
	void moveTail();

	void draw(sf::RenderWindow & t_window);
};

