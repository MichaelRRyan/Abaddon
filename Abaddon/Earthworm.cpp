// @Author Michael Rainsford Ryan

#include "MyVector2.h"
#include "Earthworm.h"



Earthworm::Earthworm()
{
	headRadius = 15.0f;
	tailRadius = 10.0f;
	tailDistanceModifier = 5.0f;

	setupShapes();
	setup();
}

void Earthworm::setup()
{
	velocity = { 0.0f, speed };
	health = 5;
	speed = 5.0f;
}

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

void Earthworm::update(sf::RenderWindow & t_window)
{
	moveTail();

	float angleRads = -4 * PI / 180;

	velocity = vectorUnitVector(static_cast<sf::Vector2f>(sf::Mouse::getPosition(t_window)) - head.getPosition()) * speed;
	head.move(velocity);
}

void Earthworm::moveTail()
{
	for (int i = TAIL_LENGTH - 1; i > 0; i--)
	{
		sf::Vector2f distanceVector = tail[i - 1].getPosition() - tail[i].getPosition();
		if (vectorLength(distanceVector) > (tailRadius * 2 - tailDistanceModifier))
		{
			sf::Vector2f movement = vectorUnitVector(distanceVector) * speed; // Get the movement direction between this tail segment and the next
			tail[i].move(movement);
		}
	}

	sf::Vector2f distanceVector = head.getPosition() - tail[0].getPosition();
	if (vectorLength(distanceVector) > (tailRadius * 2 - tailDistanceModifier))
	{
		sf::Vector2f movement = vectorUnitVector(distanceVector) * speed; // Get the movement direction between this tail segment and the next
		tail[0].move(movement);
	}
}

void Earthworm::draw(sf::RenderWindow & t_window)
{
	t_window.draw(head);
	for (int i = 0; i < TAIL_LENGTH; i++)
	{
		t_window.draw(tail[i]);
	}
}
