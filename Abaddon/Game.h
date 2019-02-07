// @Author Michael Rainsford Ryan
#ifndef GAME
#define GAME

#include <SFML\Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include "Globals.h"
#include "Player.h"
#include "Crow.h"
#include "Bullet.h"
#include "Earthworm.h"
#include "Gun.h"

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void processEvents();
	void loadContent();
	void update(float t_delta);
	void render();
	bool checkMoveInput(int t_direction); // Checks for input and returns the correct direction to allow for multiple movement keys
	void manageMovement(); // Send the input to the player object
	void respawnEnemies(); // Respawn the enemies
	
	sf::RenderWindow m_window;
	bool m_exitGame;
	enum GameStates { MainMenu, GamePlaying, Pause, Restart };

	// Game control
	bool m_gameActive{ true };
	GameStates m_gameState{ GamePlaying };
	float m_score{ 0 };

	// Setup the shapes
	sf::RectangleShape m_leftWall;
	sf::RectangleShape m_rightWall;

	sf::RectangleShape m_healthBar;
	sf::RectangleShape m_statusBar;
	sf::RectangleShape m_miniMenu;

	// Setup the game objects
	Player player;
	Crow crow;
	Earthworm earthworm;
	Gun playerGun;
	

	// Declare UI components
	sf::Font m_impactFont;
	sf::Text m_scoreText;
	sf::Text m_gameOverText;
	sf::Text m_restartText;
};




#endif // !GAME