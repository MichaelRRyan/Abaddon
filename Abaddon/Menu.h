// @Author Michael Rainsford Ryan

#pragma once

#include "Globals.h"
#include <SFML\Graphics.hpp>
#include <string>

const int BUTTON_WIDTH{ 200 };
const int BUTTON_HEIGHT{ 60 };

class Menu
{
	sf::RectangleShape playButton;
	sf::RectangleShape helpButton;
	sf::RectangleShape quitButton;

	sf::Font impactFont;

	sf::Text playText;
	sf::Text helpText;
	sf::Text quitText;
public:
	Menu();
	void clickButton(int t_buttonNum);
	void drawMenu(sf::RenderWindow & t_window);
	void setupText(sf::Text & t_text, std::string t_string, sf::Vector2f t_position);
	void loadFont();
};

