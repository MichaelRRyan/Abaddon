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
				fireBullet(nextEvent);
			}
		}
	}
}

void Game::fireBullet(sf::Event t_mouseEvent)
{
	sf::Vector2i mousePosition = { t_mouseEvent.mouseButton.x, t_mouseEvent.mouseButton.y };
	sf::Vector2f distanceVector = static_cast<sf::Vector2f>(mousePosition) - player.getPosition();
	float distanceMagnitude = sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);
	sf::Vector2f bulletDirection = distanceVector / distanceMagnitude;

	// Loop to find a non active bullet to fire
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (!bullets[i].getActive())
		{
			bullets[i].intialise(player.getPosition(), bulletDirection, 5.0f, 1);
			break;
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
}

// Updates the game world
void Game::update(float t_delta)
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

	if (player.getActive()) // If the player is alive
	{
		player.update();
	}
	if (crow.getActive()) // update the crow if active
	{
		crow.update(player, m_score);
	}

	// Update all active bullets
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].getActive())
		{
			bullets[i].update();
			if (bullets[i].isColliding(crow.getBody()) && crow.getActive())
			{
				crow.changeHealth(-bullets[i].getDamage());
				bullets[i].setActive(false);
			}
		}
	}

	// Update the score and text
	if (m_gameActive)
	{
		m_score += 5 / t_delta;
		m_scoreText.setString("SCORE: " + std::to_string(static_cast<int>(m_score)));
	}

	m_healthBar.setScale(static_cast<float>(1.0f * player.getHealth() / MAX_HEALTH), 1.0f);

	if (!player.getActive())
	{
		m_gameActive = false;
	}
}

// Draws the game world and window
void Game::render()
{
	m_window.clear(sf::Color{ 90, 60, 30 }); // Clear the screen to a brown/cave colour

	if (player.getActive())
	{
		m_window.draw(player.getBody());
	}
	if (crow.getActive())
	{
		m_window.draw(crow.getBody());
	}

	m_window.draw(m_leftWall);
	m_window.draw(m_rightWall);

	// Draw all active bullets
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].getActive())
		{
			m_window.draw(bullets[i].getBody());
		}
	}

	m_window.draw(m_statusBar);
	m_window.draw(m_scoreText);
	m_window.draw(m_healthBar);

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
