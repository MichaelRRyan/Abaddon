// @Author Michael Rainsford Ryan
#include "Gun.h"

Gun::Gun()
{
	setupSounds();
	speed = 10.0f;
	damage = 2;
	coolDown = 15; // The cooldown everytime a bullet is fired
	coolDownTimer = 0; // The current cooldown until another bullet can be fired
}

void Gun::setupSounds()
{
	if (!gunshotSoundBuffer.loadFromFile("ASSETS\\AUDIO\\gunshot.wav"))
	{
		std::cout << "Error Loading Gunshot Sound";
	}
	gunshotSound.setBuffer(gunshotSoundBuffer);
}

void Gun::fireBullet(sf::Vector2f t_position, sf::Vector2f t_target, int & t_screenShakeTimer)
{
	if (coolDownTimer <= 0)
	{
		sf::Vector2f distanceVector = t_target - t_position;
		sf::Vector2f bulletDirection = vectorUnitVector(distanceVector);

		// Loop to find a non active bullet to fire
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (!bullets[i].getActive())
			{
				bullets[i].intialise(t_position, bulletDirection, speed, damage);
				coolDownTimer = coolDown;
				gunshotSound.play();
				t_screenShakeTimer = 15; // screen shake for half a second
				break;
			}
		}
	}
}

void Gun::updateBullets(Crow t_crows[], int t_maxCrows, Earthworm t_eartworms[], int t_maxEarthworms)
{
	// Update all active bullets
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].getActive()) // If the current bullet is active
		{
			bullets[i].update(); // Update the bullet
			checkBulletCollisions(bullets[i], t_crows, t_maxCrows, t_eartworms, t_maxEarthworms);
		}
	}

	// Cooldown the gun over time
	if (coolDownTimer > 0)
	{
		coolDownTimer--;
	}
}

void Gun::checkBulletCollisions(Bullet & t_bullet, Crow t_crows[], int t_maxCrows, Earthworm t_eartworms[], int t_maxEarthworms)
{
	// Check collisions agains all crows
	for (int i = 0; i < t_maxCrows; i++)
	{
		if (t_bullet.isColliding(t_crows[i].getBody()) && t_crows[i].getActive()) // If the crow is active and the colliding with a bullet
		{
			t_crows[i].changeHealth(-t_bullet.getDamage()); // Damage the crow
			t_bullet.setActive(false); // Deactivate the colliding bullet
		}
	}
	
	// Check collisions against all earthworms
	for (int i = 0; i < t_maxEarthworms; i++)
	{
		if (t_eartworms[i].isColliding(t_bullet.getPosition(), t_bullet.getCollisionRadius()) && t_eartworms[i].getActive()) // If the crow is active and the colliding with a bullet
		{
			t_eartworms[i].changeHealth(-t_bullet.getDamage()); // Damage the crow
			t_bullet.setActive(false); // Deactivate the colliding bullet
		}
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


