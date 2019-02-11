#include "Menu.h"



Menu::Menu()
{
	playButton.setSize({ static_cast<float>(BUTTON_WIDTH), static_cast<float>(BUTTON_HEIGHT) });
	helpButton.setSize({ static_cast<float>(BUTTON_WIDTH), static_cast<float>(BUTTON_HEIGHT) });
	quitButton.setSize({ static_cast<float>(BUTTON_WIDTH), static_cast<float>(BUTTON_HEIGHT) });

	playButton.setPosition(static_cast<float>((WINDOW_WIDTH - BUTTON_WIDTH) / 2), 400.0f);
	helpButton.setPosition(static_cast<float>((WINDOW_WIDTH - BUTTON_WIDTH) / 2), 500.0f);
	quitButton.setPosition(static_cast<float>((WINDOW_WIDTH - BUTTON_WIDTH) / 2), 600.0f);

	setupText(playText, "START", { WINDOW_WIDTH / 2, 400 });
	setupText(helpText, "HELP", { WINDOW_WIDTH / 2, 500 });
	setupText(quitText, "QUIT", { WINDOW_WIDTH / 2, 600 });
}

void Menu::clickButton(int t_buttonNum)
{
}

void Menu::drawMenu(sf::RenderWindow & t_window)
{
	t_window.draw(playButton);
	t_window.draw(helpButton);
	t_window.draw(quitButton);

	t_window.draw(playText);
	t_window.draw(helpText);
	t_window.draw(quitText);
}

void Menu::setupText(sf::Text & t_text, std::string t_string, sf::Vector2f t_position)
{
	t_text.setFont(impactFont);
	t_text.setCharacterSize(20);
	t_text.setString(t_string);
	t_text.setPosition(t_position);
	t_text.setFillColor(sf::Color::Black);
}

void Menu::loadFont()
{
	if (!impactFont.loadFromFile("ASSETS\\FONT\\impact.ttf"))
	{
		// Error
	}
}
