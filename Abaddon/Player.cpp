// @Author Michael Rainsford Ryan
#include "Player.h"


// Initialise the player object
Player::Player()
{
	loadFiles();
	setup();
}

// Setup the player values
void Player::setup()
{
	wallLaunchSpeed = 10.0f;
	wallMovementLockTime = 30;

	body.setPosition(300.0f, 400.0f);

	speed = 5.0f;
	health = MAX_HEALTH;
	velocity = { 0.0f,0.0f };
	friction = 0.96f;
	movementLockTimer = 0;
}

// Load and set up the files
void Player::loadFiles()
{
	if (!spriteSheet.loadFromFile("ASSETS\\IMAGES\\player_down.png"))
	{
		// Failed to load sprite
	}

	body.setTexture(spriteSheet);
	body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
}

// Return the position of the object
sf::Vector2f Player::getPosition()
{
	return body.getPosition();
}

// Return the body of the player
sf::Sprite Player::getBody()
{
	return body;
}

int Player::getHealth()
{
	return health;
}

bool Player::getActive()
{
	return active;
}

// Move the player up
void Player::moveUp()
{
	moveDir.y = -1.0f; // Set verticle move direction to up
}

// Move the player down
void Player::moveDown()
{
	moveDir.y = 1.0f; // Set verticle move direction to down
}

// Move the player left
void Player::moveLeft()
{
	moveDir.x = -1.0f; // Set horisontal move direction to left
}

// Move the player right
void Player::moveRight()
{
	moveDir.x = 1.0f; // Set horisontal move direction to right
}

// Update the player
void Player::update()
{
	if (movementLockTimer <= 0)
	{
		body.setColor(sf::Color::White);

		if (vectorLength(moveDir) != 0.0f) // If the player has moved, update their velocity
		{
			if (moveDir.x == 0.0f) // If the player hasn't moved horisontally, only update the vertical axis
			{
				velocity.y = moveDir.y * speed;
			}
			else if (moveDir.y == 0.0f) // If the player hasn't moved vertically, only update the horisontal axis
			{
				velocity.x = moveDir.x * speed;
			}
			else // If the player moved along both axis, set the velocity to the direction times speed to keep movement equal
			{
				velocity = vectorUnitVector(moveDir) * speed;
			}
		}
	}
	else
	{
		body.setColor(sf::Color::Red);
		movementLockTimer--;
	}

	velocity *= friction; // Apply friction
	body.move(velocity); // Move the player by the velocity
	moveDir = { 0.0f, 0.0f }; // Reset the move direction for next frame

	wallCollisions();

	if (health <= 0)
	{
		die();
	}
}

void Player::die()
{
	health = 0;
	active = false;
}

// Handle collisions between the player and the wall
void Player::wallCollisions()
{
	// Check horisontal collisions
	if (body.getPosition().x < WALL_WIDTH + body.getGlobalBounds().width / 2) // Check the left wall collisions
	{
		body.setPosition(WALL_WIDTH + body.getGlobalBounds().width / 2, body.getPosition().y); // Set the position to the wall position in case of overlap
		velocity.x = wallLaunchSpeed; // Launch the player off the wall
		damage(1, wallMovementLockTime); // Damage and freeze the player
	}
	else if (body.getPosition().x > WINDOW_WIDTH - WALL_WIDTH - body.getGlobalBounds().width / 2) // Check the right wall collisions
	{
		body.setPosition(WINDOW_WIDTH - WALL_WIDTH - body.getGlobalBounds().width / 2, body.getPosition().y); // Set the position to the wall position in case of overlap
		velocity.x = -wallLaunchSpeed; // Launch the player off the wall
		damage(1, wallMovementLockTime); // Damage and freeze the player
	}

	// Check vertical collsions
	if (body.getPosition().y > WINDOW_HEIGHT - body.getGlobalBounds().height / 2) // Check the right wall collisions
	{
		body.setPosition(body.getPosition().x, WINDOW_HEIGHT - body.getGlobalBounds().height / 2);
	}
	else if (body.getPosition().y < WINDOW_HEIGHT_BEGINNING + body.getGlobalBounds().height / 2)
	{
		body.setPosition(body.getPosition().x, WINDOW_HEIGHT_BEGINNING + body.getGlobalBounds().height / 2);
	}
}

// Deal damage to the player and freeze movement for an amount of time
void Player::damage(int t_damageValue, int t_freezeTime)
{
	movementLockTimer = t_freezeTime;
	health -= t_damageValue;
}

