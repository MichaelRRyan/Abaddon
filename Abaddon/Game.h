// @Author Michael Rainsford Ryan
#ifndef GAME
#define GAME

#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Player.h"

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

	sf::CircleShape m_circle;
	Player player;
};




#endif // !GAME