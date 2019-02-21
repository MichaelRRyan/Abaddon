// @Author Michael Rainsford Ryan
#pragma once
#include "MyVector2.h"


const int WEST{ 1 };
const int EAST{ 2 };
const int NORTH{ 3 };
const int SOUTH{ 4 };

const float WINDOW_WIDTH{ 600.0f };
const float WINDOW_HEIGHT{ 800.0f };
const float WINDOW_HEIGHT_BEGINNING{ 100.0f };

const float WALL_WIDTH{ 50.0f };

const int MAX_HEALTH{ 5 };

class Global
{
public:
	// Global functions
	static bool isColliding(sf::Vector2f t_posOne, float t_radiusOne, sf::Vector2f t_posTwo, float t_radiusTwo)
	{
		sf::Vector2f distanceVector = t_posTwo - t_posOne; // Gets the distance vector between the two points
		if (vectorLength(distanceVector) < t_radiusOne + t_radiusTwo)
		{
			return true;
		}
		return false;
	}
};