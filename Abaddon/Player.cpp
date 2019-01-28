#include "Player.h"



Player::Player()
{
	loadFiles();
	setup();
}

void Player::setup()
{
	speed = 5.0f;
	health = 5;
	velocity = { 0.0f,0.0f };
	friction = 0.95;
}

void Player::loadFiles()
{
	if (!spriteSheet.loadFromFile("ASSETS\\IMAGES\\player_down.png"))
	{
		// Failed to load sprite
	}

	body.setTexture(spriteSheet);
}

sf::Sprite Player::getBody()
{
	return body;
}

void Player::moveUp()
{
	moveDir.y = -1.0f;
}

void Player::moveDown()
{
	moveDir.y = 1.0f;
}

void Player::moveLeft()
{
	moveDir.x = -1.0f;
}

void Player::moveRight()
{
	moveDir.x = 1.0f;
}

void Player::update()
{
	if (vectorLength(moveDir) != 0.0f) // If the player has moved, update they're velocity
	{
		if (moveDir.x == 0.0f)
		{
			velocity.y = moveDir.y * speed;
		}
		else if (moveDir.y == 0.0f)
		{
			velocity.x = moveDir.x * speed;
		}
		else
		{
			velocity = vectorUnitVector(moveDir) * speed;
		}
	}

	body.move(velocity);
	velocity *= friction;
	moveDir = { 0.0f, 0.0f };
}

