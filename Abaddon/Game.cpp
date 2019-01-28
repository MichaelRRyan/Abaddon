/// ========================= Abaddon ==========================
/// An endless falling game where you must survive the monsters
/// of an endless pit as you descend into the depths, earning
/// more points as you descend.
/// ============================================================
/// @Author Michael Rainsford Ryan
/// @Date 28/01/2019
/// C00239510
/// Estimated time: 4h
///

//////////////////////////////////////////////////////////// 
// include correct library file for release and debug versions
//////////////////////////////////////////////////////////// 

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



int main()
{
	Game game;
	game.run();

	return 0;
}

Game::Game() :
	m_window{ sf::VideoMode{ static_cast<unsigned>(WINDOW_WIDTH), static_cast<unsigned>(WINDOW_HEIGHT) }, "Abaddon" },
	m_exitGame{ false }
{
	loadContent();
}


Game::~Game()
{
}

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

void Game::loadContent()
{
	m_circle.setPosition(sf::Vector2f{ 400.0f, 300.0f });
	m_circle.setRadius(30.0f);
	m_circle.setFillColor(sf::Color::Red);
}

void Game::update(sf::Time t_delta)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.moveUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.moveDown();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.moveLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.moveRight();
	}

	player.update();
}

void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_circle);
	m_window.draw(player.getBody());

	m_window.display();
}
