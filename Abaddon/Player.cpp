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
	health = 5;
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
}

void Player::wallCollisions()
{
	if (body.getPosition().x < WALL_WIDTH)
	{
		body.setPosition(WALL_WIDTH, body.getPosition().y);
		velocity.x = wallLaunchSpeed;
		movementLockTimer = wallMovementLockTime;
		health--;
	}
	if (body.getPosition().x + body.getGlobalBounds().width > WINDOW_WIDTH - WALL_WIDTH)
	{
		body.setPosition(WINDOW_WIDTH - WALL_WIDTH - body.getGlobalBounds().width, body.getPosition().y);
		velocity.x = -wallLaunchSpeed;
		movementLockTimer = wallMovementLockTime;
		health--;
	}
}

