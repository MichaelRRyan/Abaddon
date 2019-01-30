// @Author Michael Rainsford Ryan
#ifndef GAME
#define GAME

#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Player.h"
#include "Crow.h"

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void processEvents();
	void loadContent();
	void update(sf::Time t_delta);
	void render();
	bool checkMoveInput(int t_direction);
	
	sf::RenderWindow m_window;
	bool m_exitGame;

	// Setup the shapes
	sf::RectangleShape m_leftWall;
	sf::RectangleShape m_rightWall;

	// Setup the game objects
	Player player;
	Crow crow;

	// Declare UI components
	sf::Font m_arialFont;
	sf::Text m_playerHealthText;
};




#endif // !GAME