#include "Obstacle.h"

/// Give the object initial values
Obstacle::Obstacle()
{
	velocity = { 0.0f,0.0f };
	speed = 4.0f;
	active = false;
	loadFiles();
}

/// Load texture files and apply them
void Obstacle::loadFiles()
{
	if (!texture.loadFromFile("ASSETS\\IMAGES\\Boulder.png"))
	{
		// Error loading boulder image
	}

	body.setTexture(texture);
	body.setTextureRect(sf::IntRect{ 0, 0, 130, 127 });
	body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2); // Set the origin of the object
	body.setScale(0.5f, 0.5f);
}

/// Respawn the object
void Obstacle::respawn()
{
	// Pick a random spot to spawn at the bottom of the screen
	float xPos = rand() / float(RAND_MAX) * (WINDOW_WIDTH - WALL_WIDTH * 2) + WALL_WIDTH;
	body.setPosition(xPos, static_cast<float>(WINDOW_HEIGHT));

	speed = rand() / float(RAND_MAX) * MAX_SPEED + MIN_SPEED; // Pick a random speed value
	float scale = MAX_SPEED / speed * BASE_SCALE; // Get a scale based off the speed
	body.setScale(scale, scale); // Set a the scale
	health = (MAX_SPEED + 1) - speed;
	velocity.y = -speed; // Set the velocity
	collisionRadius = body.getGlobalBounds().width / 2; // Set the collision radius based on the size of the object

	active = true;
}

/// Update the object if active
void Obstacle::update()
{
	if (active)
	{
		body.move(velocity);
		if (body.getPosition().y < WINDOW_HEIGHT_BEGINNING)
		{
			active = false;
		}
	}
}

/// Draw the object if active
void Obstacle::draw(sf::RenderWindow & t_window)
{
	if (active)
	{
		t_window.draw(body);
	}
}

/// Return the body of the object
sf::Sprite Obstacle::getBody()
{
	return sf::Sprite();
}
