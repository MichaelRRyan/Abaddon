// @Author Michael Rainsford Ryan
#include "Bullet.h"



Bullet::Bullet()
{
	active = false;
	loadFiles();
}

void Bullet::loadFiles()
{
	if (!spriteTexture.loadFromFile("ASSETS\\IMAGES\\fireball_right.png"))
	{
		// Error loading fireball image
	}

	body.setTexture(spriteTexture);
	body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
}

int Bullet::getDamage()
{
	return damage;
}

sf::Sprite Bullet::getBody()
{
	return body;
}

bool Bullet::getActive()
{
	return active;
}

void Bullet::setActive(bool t_active)
{
	active = t_active;
}

void Bullet::intialise(sf::Vector2f t_position ,sf::Vector2f t_direction, float t_speed, int t_damage)
{
	float rotationAngle = atan2f(t_direction.y, t_direction.x) * 180/ 3.14;
	body.setRotation(rotationAngle);
	body.setPosition(t_position);
	velocity = t_direction * t_speed;
	damage = t_damage;
	active = true;
}

bool Bullet::isColliding(sf::Sprite t_collider)
{
	if (body.getGlobalBounds().intersects(t_collider.getGlobalBounds()))
	{
		return true;
	}

	return false;
}

void Bullet::update()
{
	body.move(velocity);

	// Check if inside bounds of screen
	if (body.getPosition().x < WALL_WIDTH || body.getPosition().x > WINDOW_WIDTH - WALL_WIDTH) // Check horisontal borders
	{
		active = false;
	}
	if (body.getPosition().y < WINDOW_HEIGHT_BEGINNING || body.getPosition().y > WINDOW_HEIGHT) // Check vertical borders
	{
		active = false;
	}
}

void Bullet::draw(sf::RenderWindow & t_window)
{
	if (active)
	{
		t_window.draw(body);
	}
}
