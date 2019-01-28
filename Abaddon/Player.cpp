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
	speed = 5.0f;
	health = 5;
	velocity = { 0.0f,0.0f };
	friction = 0.95;
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

// Return the body of the player
sf::Sprite Player::getBody()
{
	return body;
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
	
	velocity *= friction; // Apply friction
	body.move(velocity); // Move the player by the velocity
	moveDir = { 0.0f, 0.0f }; // Reset the move direction for next frame
}

