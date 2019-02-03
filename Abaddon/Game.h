// @Author Michael Rainsford Ryan
#ifndef GAME
#define GAME

#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Player.h"
#include "Crow.h"
#include "Bullet.h"

const int MAX_BULLETS{ 10 };

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void processEvents();
	void fireBullet(sf::Event t_mouseEvent);
	void loadContent();
	void update(float t_delta);
	void render();
	bool checkMoveInput(int t_direction);
	
	sf::RenderWindow m_window;
	bool m_exitGame;

	// Game control
	bool m_gameActive{ true };
	float m_score{ 0 };

	// Setup the shapes
	sf::RectangleShape m_leftWall;
	sf::RectangleShape m_rightWall;

	sf::RectangleShape m_healthBar;
	sf::RectangleShape m_statusBar;

	// Setup the game objects
	Player player;
	Crow crow;
	Bullet bullets[MAX_BULLETS];

	// Declare UI components
	sf::Font m_impactFont;
	sf::Text m_scoreText;
};




#endif // !GAME