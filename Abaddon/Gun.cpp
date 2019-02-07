// @Author Michael Rainsford Ryan
#include "Gun.h"

Gun::Gun()
{
	speed = 10.0f;
	damage = 1;
	coolDown = 30; // The cooldown everytime a bullet is fired
	coolDownTimer = 0; // The current cooldown until another bullet can be fired
}

void Gun::fireBullet(sf::Vector2f t_position, sf::Vector2f t_target)
{
	sf::Vector2f distanceVector = t_target - t_position;
	sf::Vector2f bulletDirection = vectorUnitVector(distanceVector);
	
	// Loop to find a non active bullet to fire
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (!bullets[i].getActive())
		{
			bullets[i].intialise(t_position, bulletDirection, speed, damage);
			break;
		}
	}
}

void Gun::updateBullets(Crow & t_crow, Earthworm & t_eartworm)
{
	// Update all active bullets
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].getActive()) // If the current bullet is active
		{
			bullets[i].update(); // Update the bullet
			checkBulletCollisions(bullets[i], t_crow, t_eartworm);
		}
	}
}

void Gun::checkBulletCollisions(Bullet & t_bullet, Crow & t_crow, Earthworm & t_eartworm)
{
	if (t_bullet.isColliding(t_crow.getBody()) && t_crow.getActive()) // If the crow is active and the colliding with a bullet
	{
		t_crow.changeHealth(-t_bullet.getDamage()); // Damage the crow
		t_bullet.setActive(false); // Deactivate the colliding bullet
	}
	if (t_eartworm.isColliding(t_bullet.getBody()) && t_eartworm.getActive()) // If the crow is active and the colliding with a bullet
	{
		t_eartworm.changeHealth(-t_bullet.getDamage()); // Damage the crow
		t_bullet.setActive(false); // Deactivate the colliding bullet
	}
}

void Gun::drawBullets(sf::RenderWindow & t_window)
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].getActive())
		{
			t_window.draw(bullets[i].getBody());
		}
	}
}

Bullet Gun::getBullet(int t_num)
{
	if (t_num < MAX_BULLETS && t_num >= 0) // return the buller if the inputted number exists in the array
	{
		return bullets[t_num];
	}

	return bullets[0]; // Return the first bullet if it the inputted number isn't in the array
}


