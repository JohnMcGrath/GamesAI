// author Peter Lowe

#include "Game.h"
#include <iostream>
#include "math.h"



Game::Game() :
	m_window{ sf::VideoMode{ 1600, 1000, 32 }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	centrePoint = sf::Vector2f(m_window.getSize().x, m_window.getSize().y);
	setupSprite(); // load texture
}


Game::~Game()
{
}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps

	m_player->Initialise();
	m_seekEnemy->Initialise(0);
	m_arriveEnemy->Initialise(1);
	m_wanderEnemy->Initialise(2);
	m_otherWanderEnemy->Initialise(3);


	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		m_player->HandleInput(event);
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	m_player->Update(centrePoint);
	m_seekEnemy->Update(m_player->getPosition(),centrePoint,0);
	m_wanderEnemy->Update(m_player->getPosition(), centrePoint, 2);
	m_otherWanderEnemy->Update(m_player->getPosition(), centrePoint, 3);
	m_arriveEnemy->Update(m_player->getPosition(), centrePoint, 1);
	temp->Update(m_player->getPosition(), m_player->getOrientation());

	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_logoSprite);
	m_window.draw(m_player->getSprite());
	m_window.draw(m_seekEnemy->getSprite());
	m_window.draw(m_wanderEnemy->getSprite());
	m_window.draw(m_otherWanderEnemy->getSprite());
	m_window.draw(m_arriveEnemy->getSprite());
	m_window.draw(temp->getSprite());
	m_window.display();
}



/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\Background.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
}
