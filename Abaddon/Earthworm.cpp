// @Author Michael Rainsford Ryan

#include "MyVector2.h"
#include "Earthworm.h"


// Initiate the worm with basic values
Earthworm::Earthworm()
{
	headRadius = 15.0f;
	tailRadius = 10.0f;
	tailDistanceModifier = 5.0f;
	velocity = { 0.0f, 0.0f };
	speed = 8.0f;
	gravityModifier = 0.1f;
	health = 5;
	inWall = true;


	setupShapes();
	spawn();
}

// Setup the worm visuals
void Earthworm::setupShapes()
{
	head.setRadius(headRadius);
	head.setFillColor(sf::Color::Red);
	head.setPosition(500.0f, 300.0f);
	head.setOrigin({ headRadius / 2, headRadius / 2 });

	for (int i = 0; i < TAIL_LENGTH; i++)
	{
		tail[i].setRadius(tailRadius);
		tail[i].setFillColor(sf::Color::Red);
		head.setOrigin({ tailRadius / 2, tailRadius / 2 });
		if (i == 0)
		{
			tail[0].setPosition(head.getPosition().x, head.getPosition().y - (tailRadius - tailDistanceModifier));
		}
		else
		{
			tail[i].setPosition(head.getPosition().x, tail[i - 1].getPosition().y - (tailRadius - tailDistanceModifier));
		}
	}
}

// Spawns the worm in a random position off the screen with the correct movement direction
void Earthworm::spawn()
{
	float yPos = rand() / float(RAND_MAX) * (WINDOW_HEIGHT - WINDOW_HEIGHT_BEGINNING) + WINDOW_HEIGHT_BEGINNING; // Pick a random Y position within the play area
	float xPos;

	if (rand() % 2 == 0) // Pick a random side of the screen to spawn on
	{
		xPos = WALL_WIDTH;
		velocity.x = speed;
	}
	else
	{
		xPos = WINDOW_WIDTH - WALL_WIDTH;
		velocity.x = -speed;
	}
	
	// Set the position of the head and tail segments
	head.setPosition(xPos, yPos);
	for (int i = 0; i < TAIL_LENGTH; i++)
	{
		tail[i].setPosition(xPos, yPos);
	}

	velocity.y = -4.0f;

	health = 5;
	active = true;
	inWall = false;
}

// Jump out to attack the player
void Earthworm::jumpAttack()
{
	float yPos = rand() / float(RAND_MAX) * (WINDOW_HEIGHT - WINDOW_HEIGHT_BEGINNING) + WINDOW_HEIGHT_BEGINNING; // Pick a random Y position within the play area
	float xPos;

	if (head.getPosition().x < WINDOW_WIDTH / 2) // jump out of the screen on the side the worm is at
	{
		xPos = WALL_WIDTH;
		velocity.x = speed;
	}
	else
	{
		xPos = WINDOW_WIDTH - WALL_WIDTH;
		velocity.x = -speed;
	}

	// Set the start position of the head and tail segments
	head.setPosition(xPos, yPos);
	for (int i = 0; i < TAIL_LENGTH; i++)
	{
		tail[i].setPosition(xPos, yPos);
	}

	velocity.y = -4.0f; // Jump height

	//health = 5;
	inWall = false;
}

// Update the worm and move it
void Earthworm::update(Player & t_player)
{
	if (active)
	{
		if (!inWall)
		{
			moveTail();

			velocity.y += gravityModifier;
			head.move(velocity);

			checkGameBounds();

			if (t_player.getActive())
			{
				playerCollisions(t_player);
			}

			if (health <= 0)
			{
				active = false;
			}
		}
		else
		{
			jumpAttack();
		}
	}
}

// Move the tail segments to follow the head
void Earthworm::moveTail()
{
	float desiredDistance = tailRadius * 2 - tailDistanceModifier;

	for (int i = TAIL_LENGTH - 1; i > 0; i--)
	{
		sf::Vector2f distanceVector = tail[i - 1].getPosition() - tail[i].getPosition();
		if (vectorLength(distanceVector) > desiredDistance)
		{
			sf::Vector2f movement = distanceVector - vectorUnitVector(distanceVector) * desiredDistance; // Get the movement direction between this tail segment and the next
			tail[i].move(movement);
		}
	}

	sf::Vector2f distanceVector = head.getPosition() - tail[0].getPosition();

	if (vectorLength(distanceVector) > desiredDistance - desiredDistance)
	{
		tail[0].move(distanceVector);
	}
}

// Check that the worm is still inside the bounds of the game window
void Earthworm::checkGameBounds()
{
	// no longer active if the last segment of the tail goes outside the screen
	if (tail[TAIL_LENGTH - 1].getPosition().x < 0.0f || tail[TAIL_LENGTH - 1].getPosition().x > WINDOW_WIDTH)
	{
		inWall = true;
	}
}

// Manage collisions between the player and worm
void Earthworm::playerCollisions(Player & t_player)
{
	if (isColliding(t_player.getBody()))
	{
		t_player.damage(1, 30);
	}
}

// Check for all parts of the worm colliding against another sprite
bool Earthworm::isColliding(sf::Sprite t_collider)
{
	bool colliding = false;

	if (head.getGlobalBounds().intersects(t_collider.getGlobalBounds())) // If the head collides with the other object colliding is true
	{
		colliding = true;
	}
	else // Only check collisions with the tail if not already collided
	{
		for (int i = 0; i < TAIL_LENGTH; i++) // Check collisions with the other object against all segments of the tail
		{
			if (tail[i].getGlobalBounds().intersects(t_collider.getGlobalBounds()))
			{
				colliding = true;
				break; // Break out of the loop if alreay colliding
			}
		}
	}

	return colliding;
}

// Draw all parts of the worm
void Earthworm::draw(sf::RenderWindow & t_window)
{
	if (active)
	{
		t_window.draw(head);
		for (int i = 0; i < TAIL_LENGTH; i++)
		{
			t_window.draw(tail[i]);
		}
	}
}
