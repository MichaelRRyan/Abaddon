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
/// Session 6: 10:40 - 12:03 - 09/02/2019 // Added arrays of enemies and changed crow sprite
/// Session 7: 09:09 - 10:58 - 20/02/2019 // Added obstacles and player collision radius
/// Extra hours worked unmarked
/// Estimated time taken: 18h
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
	setupGame(); // Restart/setup the game
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
		if (player.getActive())
		{
			if (nextEvent.type == sf::Event::MouseButtonPressed)
			{
				if (nextEvent.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePosition = { nextEvent.mouseButton.x, nextEvent.mouseButton.y };
					playerGun.fireBullet(player.getPosition(), static_cast<sf::Vector2f>(mousePosition), m_screenShakeTimer);
				}
			}
		}
		if (m_gameState == Restart)
		{
			if (nextEvent.type == sf::Event::KeyPressed)
			{
				if (nextEvent.key.code == sf::Keyboard::R)
				{
					setupGame();
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

	m_gameOverText.setFont(m_impactFont);
	m_gameOverText.setPosition(WINDOW_WIDTH / 2 - 90.0f, WINDOW_HEIGHT / 2 - 150.0f);
	m_gameOverText.setCharacterSize(50u);
	m_gameOverText.setFillColor(sf::Color::Red);
	m_gameOverText.setOutlineColor(sf::Color::Black);
	m_gameOverText.setOutlineThickness(0.5f);
	m_gameOverText.setString("YOU DIED");

	m_restartText.setFont(m_impactFont);
	m_restartText.setPosition(WINDOW_WIDTH / 2 - 120.0f, WINDOW_HEIGHT / 2);
	m_restartText.setCharacterSize(30u);
	m_restartText.setFillColor(sf::Color::White);
	m_restartText.setOutlineColor(sf::Color::Black);
	m_restartText.setOutlineThickness(0.5f);
	m_restartText.setString("Press 'R' To Restart");

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

	m_miniMenu.setSize(sf::Vector2f{ 400.0f, 500.0f });
	m_miniMenu.setPosition(100.0f, 150.0f);
	m_miniMenu.setFillColor(sf::Color{ 50, 160, 85, 155 });
	m_miniMenu.setOutlineColor(sf::Color::Black);
	m_miniMenu.setOutlineThickness(2.0f);

	for (int i = 0; i < MAX_PARTICLES; i++) // Move all the particles up constantly
	{
		playerParticles[i].setSize({ 8.0f, 8.0f });
		playerParticles[i].setOrigin(4.0f, 4.0f);
		playerParticles[i].setFillColor(sf::Color{ 255,255,255,80 });
	}
}

// Updates the game world
void Game::update(float t_delta)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (m_screenShakeTimer > 0) // Decriment the screenshake timer if it's greater than 0
	{
		m_screenShakeTimer--;
		viewShake();

		if (m_screenShakeTimer <= 0) // If the view shake timer has just stopped, reset the view
		{
			m_window.setView(sf::View{ sf::FloatRect(0.0f, 0.0f, static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y)) });
		}
	}
		

	// Update the score and text
	switch (m_gameState)
	{
	case Game::MainMenu:
		// Add main menu functionality here
		break;
	case Game::GamePlaying: // Game playing state
		manageCollisions();

		manageMovement(); // Manage the input and move the player accordingly
		player.update(); // Update the player when active
		updateParticles();
		
		updateNonPlayer();

		m_score += 5 / t_delta;
		m_distance += 5 / t_delta;
		m_scoreText.setString("SCORE: " + std::to_string(static_cast<int>(m_score)));
		m_healthBar.setScale(static_cast<float>(1.0f * player.getHealth() / MAX_HEALTH), 1.0f); // Update the healthbar GUI

		if (!player.getActive())
		{
			m_gameState = Restart;
			m_scoreText.setPosition(WINDOW_WIDTH / 2.0f - 85.0f, WINDOW_HEIGHT / 2.0f - 75.0f);
			m_scoreText.setCharacterSize(40u);

		}

		respawnEnemies();
		break;
	case Game::Pause:
		// Add pause menu functionality here
		break;
	case Game::Restart: // Restart menu

		updateNonPlayer();

		break;
	}
}

// Draws the game world and window
void Game::render()
{
	m_window.clear(sf::Color{ 90, 60, 30 }); // Clear the screen to a brown/cave colour

	// Draw the game characters
	for (int i = 0; i < MAX_PARTICLES; i++) // Draw all particals
	{
		m_window.draw(playerParticles[i]);
	}
	player.draw(m_window);

	// Draw the crows
	for (int i = 0; i < MAX_CROWS; i++)
	{
		crows[i].draw(m_window);
	}
	
	// Draw the earthworms
	for (int i = 0; i < MAX_EARTHWORMS; i++)
	{
		earthworms[i].draw(m_window);
	}

	// Draw the bullets
	playerGun.drawBullets(m_window);

	obstacle.draw(m_window);

	// Draw the game world
	m_window.draw(m_leftWall);
	m_window.draw(m_rightWall);

	// Draw the GUI
	m_window.draw(m_statusBar);
	m_window.draw(m_healthBar);

	if (m_gameState == Restart)
	{
		m_window.draw(m_miniMenu);
		m_window.draw(m_gameOverText);
		m_window.draw(m_restartText);
	}

	m_window.draw(m_scoreText);

	if (m_gameState == MainMenu)
	{
		mainMenu.drawMenu(m_window);
	}

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

// Respawn inactive/dead enemies
void Game::respawnEnemies()
{
	int maxSpawnTimeModifier = 8;
	int crowSpawnTime = 60; // Minimum crow spawn time
	int wormSpawnTime = 120; // Minimum worm spawn time

	// Decrease spawn time as game goes on
	int respawnMax = static_cast<int>(m_distance / 5.0f); // Get a fraction of the distance travelled

	int potentialSpawnTime = crowSpawnTime * maxSpawnTimeModifier - respawnMax;
	if (crowSpawnTime < potentialSpawnTime)
	{
		crowSpawnTime = potentialSpawnTime;
	}

	potentialSpawnTime = wormSpawnTime * maxSpawnTimeModifier - respawnMax;
	if (wormSpawnTime < potentialSpawnTime)
	{
		wormSpawnTime = potentialSpawnTime;
	}

	// Respawn the crow if not already active
	if (rand() % crowSpawnTime == 0)
	{
		for (int i = 0; i < MAX_CROWS; i++)
		{
			if (!crows[i].getActive())
			{
				float randomX = rand() / float(RAND_MAX) * (WINDOW_HEIGHT - WALL_WIDTH * 2) - WALL_WIDTH; // Get a random float value with the range of the active screen width
				crows[i].setPosition(randomX, WINDOW_HEIGHT_BEGINNING + crows[i].getBody().getGlobalBounds().height / 2); // Set the position of the crow
				crows[i].setup(); // Setup the crow again (respawn it)
				break;
			}
		}
	}

	// Respawn the worm
	if (rand() % wormSpawnTime == 0)
	{
		for (int i = 0; i < MAX_EARTHWORMS; i++)
		{
			if (!earthworms[i].getActive())
			{
				earthworms[i].spawn();
				break;
			}
		}
	}

	if (rand() % 120 == 0 && !obstacle.getActive())
	{
		obstacle.respawn();
	}
}

void Game::setupGame()
{
	player.setup();
	for (int i = 0; i < MAX_CROWS; i++)
	{
		crows[i].setActive(false);
	}
	for (int i = 0; i < MAX_EARTHWORMS; i++)
	{
		earthworms[i].setActive(false);
	}
	obstacle.setActive(false);

	m_scoreText.setPosition(WINDOW_WIDTH / 2 - 70.0f, 50.0f);
	m_scoreText.setCharacterSize(30u);
	m_score = 0.0f;
	m_distance = 0.0f;
	m_gameState = GamePlaying;
}

// Update the non player objects
void Game::updateNonPlayer()
{
	obstacle.update();
	playerGun.updateBullets(crows, MAX_CROWS, earthworms, MAX_EARTHWORMS); // Update all active player bullets

	// Update all the crows
	for (int i = 0; i < MAX_CROWS; i++)
	{
		crows[i].update(player, m_score); // Update the crow when active
	}

	// Update all the earthworms
	for (int i = 0; i < MAX_EARTHWORMS; i++)
	{
		earthworms[i].update(player); // Update the earthworm when active
	}
}

void Game::manageCollisions()
{
	sf::Vector2f distanceVector = player.getPosition() - obstacle.getPosition();
	if (vectorLength(distanceVector) < player.getCollisionRadius() + obstacle.getCollisionRadius())
	{
		player.damage(1, 15);
	}
}

// Shakes the screen for a preset amount time
void Game::viewShake()
{
	if (m_screenShakeTimer % 3 > 1) // Only shake the screen every three frames
	{
		m_window.setView(sf::View{ sf::FloatRect(static_cast<float>(rand() % 16 - 8), static_cast<float>(rand() % 16 - 8), static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y)) });
	}
}

void Game::updateParticles()
{
	// (particleNum / 6 is to give delay between particles)
	(particleNum / 6 < MAX_PARTICLES) ? particleNum++ : particleNum = 0; // Increase the particle number until it reaches max and then reset
	playerParticles[particleNum / 6].setPosition(player.getPosition());

	for (int i = 0; i < MAX_PARTICLES; i++) // Move all the particles up constantly
	{
		playerParticles[i].move(0.0f, -8.0f);
	}
}
