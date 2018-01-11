
#include "Game.h"
#include <iostream>




Game::Game() :
	m_window{ sf::VideoMode{ 1600, 1000, 32 }, "Space Game" },
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
	srand(time(NULL));

	m_player->Initialise();
	m_arriveEnemy->Initialise(1);
	playerView.setSize(sf::Vector2f(VIEW_HEIGHT,VIEW_HEIGHT));
	enemies.push_back(m_arriveEnemy);

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
void Game::ResizeView(const sf::RenderWindow& window, sf::View view)
{
	float ratio = float(window.getSize().x) / float(window.getSize().y);
	playerView.setSize(sf::Vector2f(VIEW_HEIGHT * ratio, VIEW_HEIGHT*ratio));
}

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

	
		if (sf::Event::Resized == event.type)
		{
			ResizeView(m_window, playerView);
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	//Player
	playerView.setCenter(m_player->getPosition());
	m_player->Update(centrePoint);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		float x = sin(m_player->getOrientation());
		float y = -cos(m_player->getOrientation());

		m_player->steerPlayer(sf::Vector2f(x, y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_player->setVelocity(sf::Vector2f(0, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_player->setOrientation(m_player->getOrientation() - (4 / (180 / 3.142))); //m_orientation -= 4 / (180 / 3.142);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_player->setOrientation(m_player->getOrientation() + (4 / (180 / 3.142)));
	}


	//Bullets
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		b1.m_shape.setPosition(m_player->getPosition());
		b1.m_velocity = normalisedAimDir * b1.m_maxSpeed;

		bullets.push_back(Bullet(b1));
	}

	playerCentre = sf::Vector2f(m_player->getPosition());

	mousePos = sf::Vector2f(10 * sin(m_player->getOrientation()) + m_player->getPosition().x, 10 * -cos(m_player->getOrientation()) + m_player->getPosition().y);

	aimDir = mousePos - playerCentre;
	normalisedAimDir = m_player->Normalise(aimDir);

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].m_shape.move(bullets[i].m_velocity);

		if (bullets[i].m_shape.getPosition().x < 0 || bullets[i].m_shape.getPosition().x > m_window.getSize().x ||
			bullets[i].m_shape.getPosition().y < 0 || bullets[i].m_shape.getPosition().y > m_window.getSize().y)
		{
			bullets.erase(bullets.begin() + i);
		}
	}

	//Enemies
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update(m_player->getPosition(), centrePoint, 1);
	}

	if (spawnCounter < 20)
	{
		spawnCounter++;
	}
	if (spawnCounter >= 20)
	{
		m_arriveEnemy->setPosition(sf::Vector2f(rand() % m_window.getSize().x, rand() % m_window.getSize().y));
		enemies.push_back(m_arriveEnemy);
		spawnCounter = 0;
	}

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
	m_window.clear(sf::Color::Black);


	m_window.setView(playerView);
	m_window.draw(m_logoSprite);

	for (size_t i = 0; i < enemies.size(); i++)
	{
		m_window.draw(enemies[i]->getSprite());
	}

	for (size_t i = 0; i < bullets.size(); i++)
	{
		m_window.draw(bullets[i].m_shape);
	}

	m_window.draw(m_player->getSprite());

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
	m_logoTexture.setRepeated(true);
}
