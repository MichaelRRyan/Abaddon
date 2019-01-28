#include "Crow.h"



Crow::Crow()
{
	loadFiles();
	setup();
}

void Crow::setup()
{
	velocity = { 0.0f, 0.0f };
	speed = 4.0f;
	health = 3;
}

void Crow::loadFiles()
{
	if (!spriteSheet.loadFromFile("ASSETS\\IMAGES\\enemy1_down.png"))
	{
		// Error can't load file
	}

	body.setTexture(spriteSheet);
}

sf::Sprite Crow::getBody()
{
	return body;
}

void Crow::update(Player t_player)
{
	attack(t_player);

	body.move(velocity);
}

void Crow::attack(Player t_player)
{
	sf::Vector2f distanceToPlayer = t_player.getPosition() - body.getPosition();
	velocity = vectorUnitVector(distanceToPlayer) * speed;
}
