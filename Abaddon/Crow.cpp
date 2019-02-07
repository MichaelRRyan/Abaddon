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
	speed = 2.5f;
	diveSpeed = 8.0f;
	health = 3;
	behaviour = Standby;
	diveRange = 80.0f;
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

// Update the crow and manage the behaviour
void Crow::update(Player & t_player, float & t_score)
{
	if (active)
	{
		if (behaviour == Standby || behaviour == Patrol) // If the behaviour is in standby or patrol, run patrol
		{
			patrol(t_player);
		}
		else
		{
			dive(t_player);
		}

		wallCollisions();

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
}

// Patrol from one side of the screen to the other
void Crow::patrol(Player t_player)
{
	// PATROL SETUP
	if (behaviour == Standby) // If in standby, set the starting velocity
	{
		if (body.getPosition().x > WINDOW_WIDTH / 2) // Check which side of the screen the crow is on
		{
			velocity = { speed, -speed / 2.0f }; // Move to right and up if that wall is closer
		}
		else
		{
			velocity = { -speed, -speed / 2.0f }; // Move to the left and up if that wall is closer
		}

		behaviour = Patrol;
	}

	// DIVE FOR THE PLAYER
	if (t_player.getActive())
	{
		if (body.getPosition().y < t_player.getPosition().y - diveHeight || // If the crow is above the player check if it's within dive range
			(body.getPosition().y < t_player.getPosition().y && t_player.getPosition().y < WINDOW_HEIGHT_BEGINNING + diveHeight)) // Or if the crow is above the player and the player is near the top of the screen
		{
			if (body.getPosition().x > t_player.getPosition().x - diveRange && body.getPosition().x < t_player.getPosition().x + diveRange) // Check that the player is within the dive range
			{
				behaviour = PrepareToDive;
			}
		}
	}
}

// Dive and attack the player, exit the state once the player is hit
void Crow::dive(Player & t_player)
{
	if (t_player.getActive())
	{
		if (behaviour == PrepareToDive) // If the crow is preparing to dive set target to player
		{
			sf::Vector2f distanceToPlayer = t_player.getPosition() - body.getPosition();
			velocity = vectorUnitVector(distanceToPlayer) * diveSpeed;
			behaviour = Dive;
		}
		else // If the crow is diving check for player collisions
		{
			if (body.getGlobalBounds().intersects(t_player.getBody().getGlobalBounds())) // If the crow collides with the player, go back to patrolling
			{
				behaviour = Standby; // Set the behaviour to the standby
				t_player.damage(attackDamage, 15); // Damage the player and stun them for 15 frames
			}
			if (body.getPosition().y > t_player.getPosition().y + diveHeight) // If the crow dives past the player go back to standby
			{
				behaviour = Standby; // Set the behaviour to the standby
			}
			if (body.getPosition().y > WINDOW_HEIGHT - body.getGlobalBounds().height / 2) // If the player dives out of the screen go to standby
			{
				behaviour = Standby; // Set the behaviour to the standby
			}
		}
	}
	else
	{
		behaviour = Standby; // Set the behaviour to the standby
	}
}

void Crow::wallCollisions()
{
	// WALL COLLISIONS
	if (body.getPosition().x < WALL_WIDTH + body.getGlobalBounds().width / 2) // Look out for left wall
	{
		velocity.x = -velocity.x;
		body.setPosition(WALL_WIDTH + body.getGlobalBounds().width / 2, body.getPosition().y);
	}
	else if (body.getPosition().x > WINDOW_WIDTH - WALL_WIDTH - body.getGlobalBounds().width / 2) // Look out for right wall
	{
		velocity.x = -velocity.x;
		body.setPosition(WINDOW_WIDTH - WALL_WIDTH - body.getGlobalBounds().width / 2, body.getPosition().y);
	}
	if (body.getPosition().y < WINDOW_HEIGHT_BEGINNING + body.getGlobalBounds().height / 2) // Check for top boundary
	{
		body.setPosition(body.getPosition().x, WINDOW_HEIGHT_BEGINNING + body.getGlobalBounds().height / 2);
		velocity.y = 0.0f;
	}
}

void Crow::draw(sf::RenderWindow & t_window)
{
	if (active)
	{
		t_window.draw(body);
	}
}
