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
/// Session 2: 16:13 - 18:21 - 01/02/2019
/// Session 3: 09:04 - 10:56 - 04/02/2019 // Added earthworm and cleaned code
/// Session 4: 20:14 - 21:00 - 04/02/2019 // Added spawn functionality to the earthworm and cleaned up code
/// Session 5: 16:03 - 17:10 - 06/02/2019 // Added a gun class to clean up bullets
///
/// ----------------------------------------------------------------------------
/// Issues
/// - Bullets don't work currently (Speed being changed)

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
	srand(static_cast<unsigned>(time(nullptr)));
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
	const float FPS{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / FPS);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		processEvents();

		timeSinceLastUpdate += clock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			update(FPS);
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
		if (nextEvent.type == sf::Event::MouseButtonPressed)
		{
			if (nextEvent.mouseButton.button == sf::Mouse::Left)
			{
				if (player.getActive())
				{
					sf::Vector2i mousePosition = { nextEvent.mouseButton.x, nextEvent.mouseButton.y };
					playerGun.fireBullet(player.getPosition(), static_cast<sf::Vector2f>(mousePosition));
				}
			}
		}
	}
}

// Load and setup the game
void Game::loadContent()
{
	if (!m_impactFont.loadFromFile("ASSETS\\FONT\\impact.ttf"))
	{
		// Error loading font file
	}

	m_scoreText.setFont(m_impactFont);
	m_scoreText.setPosition(WINDOW_WIDTH / 2 - 70.0f, 50.0f);
	m_scoreText.setCharacterSize(30u);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setOutlineColor(sf::Color::Black);
	m_scoreText.setOutlineThickness(1.0f);
	m_scoreText.setString("SCORE: ");

	m_leftWall.setPosition(0.0f, 0.0f);
	m_rightWall.setPosition(WINDOW_WIDTH - WALL_WIDTH, 0.0f);

	m_leftWall.setSize({ WALL_WIDTH, WINDOW_HEIGHT });
	m_rightWall.setSize({ WALL_WIDTH, WINDOW_HEIGHT });

	m_leftWall.setFillColor(sf::Color{ 60, 40, 20 });
	m_rightWall.setFillColor(sf::Color{ 60, 40, 20 });

	m_healthBar.setSize(sf::Vector2f{ 300.0f, 20.0f });
	m_healthBar.setOutlineColor(sf::Color::Black);
	m_healthBar.setOutlineThickness(2.0f);
	m_healthBar.setOrigin(150.0f, 10.0f);
	m_healthBar.setPosition(WINDOW_WIDTH / 2.0f, 30.0f);
	m_healthBar.setFillColor(sf::Color::Red);

	m_statusBar.setSize(sf::Vector2f{ WINDOW_WIDTH, WINDOW_HEIGHT_BEGINNING });
	m_statusBar.setPosition(0.0f, 0.0f);
	m_statusBar.setFillColor(sf::Color{ 50, 160, 85 });
	m_statusBar.setOutlineColor(sf::Color::Black);
	m_statusBar.setOutlineThickness(2.0f);

	earthworm.spawn();
}

// Updates the game world
void Game::update(float t_delta)
{
	if (m_exitGame)
	{
		m_window.close();
	}


	// Respawn the crow if not already active
	if (!crow.getActive() && rand() % 120 == 0)
	{
		float randomX = rand() / float(RAND_MAX) * (WINDOW_HEIGHT - WALL_WIDTH * 2) - WALL_WIDTH; // Get a random float value with the range of the active screen width
		crow.setPosition(randomX, WINDOW_HEIGHT_BEGINNING); // Set the position of the crow
		crow.setup(); // Setup the crow again (respawn it)
	}

	if (!earthworm.getActive() && rand() % 240 == 0)
	{
		earthworm.spawn();
	}

	manageMovement(); // Manage the input and move the player accordingly

	if (player.getActive()) // If the player is alive
	{
		player.update();
	}
	if (crow.getActive()) // update the crow if active
	{
		crow.update(player, m_score);
	}

	// Update all active player bullets
	playerGun.updateBullets(crow, earthworm);

	earthworm.update(player);

	// Update the score and text
	if (m_gameActive)
	{
		m_score += 5 / t_delta;
		m_scoreText.setString("SCORE: " + std::to_string(static_cast<int>(m_score)));
	}

	m_healthBar.setScale(static_cast<float>(1.0f * player.getHealth() / MAX_HEALTH), 1.0f); // Update the healthbar GUI

	if (!player.getActive())
	{
		m_gameActive = false;
	}
}

// Draws the game world and window
void Game::render()
{
	m_window.clear(sf::Color{ 90, 60, 30 }); // Clear the screen to a brown/cave colour

	// Draw the game characters
	player.draw(m_window);
	crow.draw(m_window);
	earthworm.draw(m_window);

	// Draw the bullets
	playerGun.drawBullets(m_window);

	// Draw the game world
	m_window.draw(m_leftWall);
	m_window.draw(m_rightWall);

	// Draw the GUI
	m_window.draw(m_statusBar);
	m_window.draw(m_scoreText);
	m_window.draw(m_healthBar);

	m_window.display();
}

// Checks for movement keys in an inputted direction to allow for multiple movement keys
bool Game::checkMoveInput(int t_direction)
{
	bool inputFound = false;

	if (t_direction == NORTH) // Check directions for north
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
	else if (t_direction == SOUTH) // Check directions for south
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
	else if (t_direction == WEST) // Check directions for west
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
	else if (t_direction == EAST) // Check directions for east
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

void Game::manageMovement()
{
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
}
