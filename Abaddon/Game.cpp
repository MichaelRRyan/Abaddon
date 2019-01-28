/// ========================= Abaddon ==========================
/// An endless falling game where you must survive the monsters
/// of an endless pit as you descend into the depths, earning
/// more points as you descend.
/// ============================================================
/// @Author Michael Rainsford Ryan
/// @Date 28/01/2019
/// C00239510
/// Estimated time: 4h
/// Session 1: 09:41 - 10:57 - 28/01/2019
/// Session 2: 12:32 - 
///

//////////////////////////////////////////////////////////// ////
// include correct library file for release and debug versions //
/////////////////////////////////////////////////////////////////

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "Game.h"


// Main entry point
int main()
{
	Game game;
	game.run();

	return 0;
}

// Default constructer
Game::Game() :
	m_window{ sf::VideoMode{ static_cast<unsigned>(WINDOW_WIDTH), static_cast<unsigned>(WINDOW_HEIGHT) }, "Abaddon" },
	m_exitGame{ false }
{
	loadContent();
}

// Default destructer
Game::~Game()
{
}

// Sets the framerate and keeps the game running
void Game::run()
{
	sf::Clock clock;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		processEvents();

		timeSinceLastUpdate += clock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			update(timePerFrame);
			render();

			timeSinceLastUpdate -= timePerFrame;
		}
	}
}

// Process and handle user events
void Game::processEvents()
{
	sf::Event nextEvent;

	while (m_window.pollEvent(nextEvent))
	{
		if (nextEvent.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

// Load and setup the game
void Game::loadContent()
{
	if (!m_arialFont.loadFromFile("ASSETS\\FONT\\arial.ttf"))
	{
		// Error loading font file
	}

	m_playerHealthText.setFont(m_arialFont);
	m_playerHealthText.setPosition(WALL_WIDTH, 0.0f);
	m_playerHealthText.setCharacterSize(20u);
	m_playerHealthText.setFillColor(sf::Color::Black);
	m_playerHealthText.setString("Health: ");

	m_circle.setPosition(sf::Vector2f{ 400.0f, 300.0f });
	m_circle.setRadius(30.0f);
	m_circle.setFillColor(sf::Color::Red);

	m_leftWall.setPosition(0.0f, 0.0f);
	m_rightWall.setPosition(WINDOW_WIDTH - WALL_WIDTH, 0.0f);

	m_leftWall.setSize({ WALL_WIDTH, WINDOW_HEIGHT });
	m_rightWall.setSize({ WALL_WIDTH, WINDOW_HEIGHT });

	m_leftWall.setFillColor(sf::Color::Yellow);
	m_rightWall.setFillColor(sf::Color::Yellow);
}

// Updates the game world
void Game::update(sf::Time t_delta)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	// Check and apply movement to the player
	if (checkMoveInput(NORTH) && !checkMoveInput(SOUTH)) // Check that the up movement is true and down movement is false
	{
		player.moveUp();
	}
	if (checkMoveInput(SOUTH) && !checkMoveInput(NORTH)) // Check that the down movement is true and up movement is false
	{
		player.moveDown();
	}
	if (checkMoveInput(WEST) && !checkMoveInput(EAST)) // Check that the left movement is true and right movement is false
	{
		player.moveLeft();
	}
	if (checkMoveInput(EAST) && !checkMoveInput(WEST)) // Check that the right movement is true and left movement is false
	{
		player.moveRight();
	}

	player.update();
	crow.update(player);
	m_playerHealthText.setString("Health: " + std::to_string(player.getHealth()));
}

// Draws the game world and window
void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_circle);
	m_window.draw(player.getBody());
	m_window.draw(crow.getBody());

	m_window.draw(m_leftWall);
	m_window.draw(m_rightWall);

	m_window.draw(m_playerHealthText);

	m_window.display();
}

// Checks for movement keys in an inputted direction to allow for multiple movement keys
bool Game::checkMoveInput(int t_direction)
{
	bool inputFound = false;

	if (t_direction == NORTH)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			inputFound = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			inputFound = true;
		}
	}
	else if (t_direction == SOUTH)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			inputFound = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			inputFound = true;
		}
	}
	else if (t_direction == WEST)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			inputFound = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			inputFound = true;
		}
	}
	else if (t_direction == EAST)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			inputFound = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			inputFound = true;
		}
	}

	return inputFound;
}
