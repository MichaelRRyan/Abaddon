// @Author Michael Rainsford Ryan
#include "Crow.h"


// Initialise the crow and values only set once
Crow::Crow()
{
	loadFiles();
	setup();
}

// Setup the changing values of the crow
void Crow::setup()
{
	velocity = { 0.0f, 0.0f };
	speed = 5.0f;
	diveSpeed = 8.0f;
	health = 3;
	behaviour = 0;
	diveRange = 10.0f;
	diveHeight = 200.0f;
	attackDamage = 1;
	active = true;
}

// Load the files and setup the sprite
void Crow::loadFiles()
{
	if (!spriteSheet.loadFromFile("ASSETS\\IMAGES\\enemy1_down.png"))
	{
		// Error can't load file
	}

	body.setTexture(spriteSheet);
	body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
}

// Change the health of the crow by the inputted value
void Crow::changeHealth(int t_changeAmount)
{
	health += t_changeAmount;
}

// Get the bodt component of the crow
sf::Sprite Crow::getBody()
{
	return body;
}

// Get the active state of the crow
bool Crow::getActive()
{
	return active;
}

// Set the position of the crow using two floats
void Crow::setPosition(float t_xPos, float t_yPos)
{
	body.setPosition(t_xPos, t_yPos);
}

// Set the position of the crow using a vector
void Crow::setPosition(sf::Vector2f t_position)
{
	body.setPosition(t_position);
}

// Update the crow and manage the behaviour
void Crow::update(Player & t_player, float & t_score)
{
	if (behaviour <= 1) // If the behaviour is in standby or patrol, run patrol
	{
		patrol(t_player);
	}
	else
	{
		attack(t_player);
	}

	float angle = atan2f(velocity.y, velocity.x) * 180 / 3.14f;
	body.setRotation(angle);

	body.move(velocity);

	// Check if still alive
	if (health <= 0)
	{
		active = false;
		t_score += 10;
	}
}

// Dive and attack the player, exit the state once the player is hit
void Crow::attack(Player & t_player)
{
	if (t_player.getActive())
	{
		sf::Vector2f distanceToPlayer = t_player.getPosition() - body.getPosition();
		velocity = vectorUnitVector(distanceToPlayer) * diveSpeed;

		if (body.getGlobalBounds().intersects(t_player.getBody().getGlobalBounds())) // If the crow collides with the player, go back to patrolling
		{
			behaviour = 0; // Set the behaviour to the standby
			t_player.damage(attackDamage, 15); // Damage the player and stun them for 15 frames
		}
	}
	else
	{
		behaviour = 0; // Set the behaviour to the standby
	}
}

// Patrol from one side of the screen to the other
void Crow::patrol(Player t_player)
{
	// PATROL SETUP
	if (behaviour == 0) // If in standby, set the starting velocity
	{
		if (body.getPosition().x > WINDOW_WIDTH / 2) // Check which side of the screen the crow is on
		{
			velocity = { speed / 2.0f, -speed / 2.0f }; // Move to right and up if that wall is closer
		}
		else
		{
			velocity = { -speed / 2.0f, -speed / 2.0f }; // Move to the left and up if that wall is closer
		}

		behaviour = 1;
	}

	// WALL COLLISIONS
	if (body.getPosition().x < WALL_WIDTH) // Look out for left wall
	{
		velocity.x = -velocity.x;
		body.setPosition(WALL_WIDTH, body.getPosition().y);
	}
	else if (body.getPosition().x > WINDOW_WIDTH - WALL_WIDTH - body.getGlobalBounds().width) // Look out for right wall
	{
		velocity.x = -velocity.x;
		body.setPosition(WINDOW_WIDTH - WALL_WIDTH - body.getGlobalBounds().width, body.getPosition().y);
	}
	if (body.getPosition().y < WINDOW_HEIGHT_BEGINNING) // Check for top boundary
	{
		body.setPosition(body.getPosition().x, WINDOW_HEIGHT_BEGINNING);
		velocity.y = 0.0f;
	}

	// DIVE FOR THE PLAYER
	if (t_player.getActive())
	{
		if (body.getPosition().y < t_player.getPosition().y - diveHeight) // If the crow is above the player check if it's within dive range
		{
			if (body.getPosition().x > t_player.getPosition().x - diveRange && body.getPosition().x < t_player.getPosition().x + diveRange) // Check that the player is within the dive range
			{
				behaviour = 2;
			}
		}
	}
}

void Crow::draw(sf::RenderWindow & t_window)
{
	if (active)
	{
		t_window.draw(body);
	}
}
