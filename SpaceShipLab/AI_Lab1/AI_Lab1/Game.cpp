#include "Game.h"
#include <iostream>



/// <summary>
///	Constructor
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1600, 1000, 32 }, "Space Game" },
	m_exitGame{false} //when true game will exit
{
	centrePoint = sf::Vector2f(m_window.getSize().x, m_window.getSize().y);
	setupSprite(); // load textures
}

/// <summary>
///	Destructor
/// </summary>
Game::~Game()
{
}

/// <summary>
///	Initial things that are done when the app starts
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps

	//Truly randomise
	srand(time(NULL));

	m_player->Initialise();
	
	//Sets the values for the view to follow the player
	playerView.setSize(sf::Vector2f(VIEW_HEIGHT,VIEW_HEIGHT));

	//Initialise the original object of each type of enemies

	//Spawn From Nests
	e1.Initialise(1);
	//Workers
	e2.Initialise(2);
	//Boids
	e3.Initialise(3);

	//Nest gets a random spawn location
	m_nestSprite.setPosition(sf::Vector2f(rand() % m_window.getSize().x, rand() % m_window.getSize().y));

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
///	Resizes the view and screen if the app window is adjusted
/// </summary>
void Game::ResizeView(const sf::RenderWindow& window, sf::View view)
{
	float ratio = float(window.getSize().x) / float(window.getSize().y);
	playerView.setSize(sf::Vector2f(VIEW_HEIGHT * ratio, VIEW_HEIGHT*ratio));
}

/// <summary>
/// Handles if the app is closed or resized.
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
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
/// Handles all events and collisions relating to the enemies and the nests
/// </summary>
void Game::EnemyHandler()
{
	if (spawnCounter < 40)
	{
		spawnCounter++;
	}

	//6 Nest will spawn on the map
	if (nests.size() < 6)
	{
		//Nest spawn randomly each time
		m_nestSprite.setPosition(sf::Vector2f(rand() % 3200, rand() % 2500));
		m_nestSprite.setOrigin(m_nestSprite.getGlobalBounds().width, m_nestSprite.getGlobalBounds().height);
		nests.push_back(m_nestSprite);
	}

	//Uses a spawn counter, no more than 5 nest enemies on screen
	if (spawnCounter >= 40 & enemies.size() < 5)
	{
		//Could spawn at any nest
		spawnCounter = 0;
		int tempNestPos = rand() % nests.size();
		e1.setPosition(sf::Vector2f(nests[tempNestPos].getPosition().x, nests[tempNestPos].getPosition().y));
		enemies.push_back(e1);
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].Update(m_player->getPosition(), centrePoint, 1);

		for (size_t j = 0; j < enemies[i].getBullets().size(); j++)
		{
			//Get player collision box
			playerBound = m_player->getSprite().getGlobalBounds();
			playerBoundShap.setSize(sf::Vector2f(playerBound.width, playerBound.height));
			playerBoundShap.setPosition(sf::Vector2f(playerBound.left, playerBound.top));

			//Get bullet of the enemy's collision box
			bulletBound = enemies[i].getBullets()[j].m_shape.getGlobalBounds();
			bulletBoundShape.setSize(sf::Vector2f(bulletBound.width, bulletBound.height));
			bulletBoundShape.setPosition(sf::Vector2f(bulletBound.left, bulletBound.top));

			if (playerBoundShap.getGlobalBounds().intersects(bulletBoundShape.getGlobalBounds()))
			{
				//The player's invincibilty turns on
				if (!m_player->getInvincible())
				{
					//Reduce Health by 10
					m_player->setInvincible(true);
					m_player->invinTimer = 0;
					m_player->setHealth(10);
					std::cout << "Player Health: " << m_player->getHealth() << std::endl;
				}
			}
		}
	}
	//Turns off after time
	if (m_player->getInvincible())
	{
		m_player->invinTimer++;
	}
	if (m_player->invinTimer >= 100)
	{
		m_player->setInvincible(false);
	}

	//Using this will cause frame stutter, commenting out increases framerate
	for (size_t i = 0; i < boids.size(); i++)
	{
		boids[i].Update(CheckForNearestWorker(boids[i].getPosition()), playerCentre, 1);
	}
}

/// <summary>
/// Handles all events and collisions relating to the workers
/// </summary>
void Game::WorkerHandler()
{
	if (workersEns.size() < 15)
	{
		std::cout << "Worker Spawned" << std::endl;
		e2.setPosition(sf::Vector2f((rand() % -500 + 500) + m_player->getPosition().x, (rand() % -500 + 500) + m_player->getPosition().y));
		workersEns.push_back(e2);
	}

	//Update loop
	for (size_t j = 0; j < workersEns.size(); j++)
	{
		workersEns[j].Update(m_player->getPosition(), centrePoint, 2);

		//Get worker collision box
		workerBound = workersEns[j].getSprite().getGlobalBounds();
		workerBoundShape.setSize(sf::Vector2f(workerBound.width, workerBound.height));
		workerBoundShape.setPosition(sf::Vector2f(workerBound.left, workerBound.top));

		//Get player collsion box
		playerBound = m_player->getSprite().getGlobalBounds();
		playerBoundShap.setSize(sf::Vector2f(playerBound.width, playerBound.height));
		playerBoundShap.setPosition(sf::Vector2f(playerBound.left, playerBound.top));

		if (workerBoundShape.getGlobalBounds().intersects(playerBoundShap.getGlobalBounds()))
		{
			//delete the worker and gain a point
			workersEns.erase(workersEns.begin() + j);
			score++;
			break;
		}
	}
}

/// <summary>
/// Handles all events and collisions relating to the player's bullets
/// </summary>
void Game::BulletHandler()
{
	//if the space key is held
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//timer
		if (bulletCounter < 10)
		{
			bulletCounter++;
		}
		else
		{
			bulletCounter = 0;
			b1.m_shape.setPosition(m_player->getPosition());
			b1.m_velocity = normalisedAimDir * b1.m_maxSpeed;

			bullets.push_back(Bullet(b1));
		}

	}
	//Gets the aiming vector between the player and a point slighty, directly ahead of the player
	playerCentre = sf::Vector2f(m_player->getPosition());
	cursorPos = sf::Vector2f(10 * sin(m_player->getOrientation()) + m_player->getPosition().x, 10 * -cos(m_player->getOrientation()) + m_player->getPosition().y);
	aimDir = cursorPos - playerCentre;
	normalisedAimDir = m_player->Normalise(aimDir);

	//Update each individual bullet
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].m_shape.move(bullets[i].m_velocity);

		//If the bullet is a distance of 2000 or more pixels from the player, the shot is deleted
		if (m_player->Magnitude(bullets[i].m_shape.getPosition() - m_player->getPosition()) > 2000)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}

		else
		{
			//Gets the bullets bounding box
			bulletBound = bullets[i].m_shape.getGlobalBounds();
			bulletBoundShape.setSize(sf::Vector2f(bulletBound.width, bulletBound.height));
			bulletBoundShape.setPosition(sf::Vector2f(bulletBound.left, bulletBound.top));

			for (size_t k = 0; k < enemies.size(); k++)
			{
				//Gets the enemy's bounding box
				enemyBound = enemies[k].getSprite().getGlobalBounds();
				enemyBoundShap.setSize(sf::Vector2f(enemyBound.width, enemyBound.height));
				enemyBoundShap.setPosition(sf::Vector2f(enemyBound.left, enemyBound.top));

				if (bulletBoundShape.getGlobalBounds().intersects(enemyBoundShap.getGlobalBounds()))
				{
					bullets.erase(bullets.begin() + i);
					//If the enemy has taken 4 hits
					enemies[k].addHitsTaken(1);
					if (enemies[k].getHitsTaken() >= 4)
					{
						enemies.erase(enemies.begin() + k);
					}
					break;
				}
			}
		}
	}
}

/// <summary>
/// Checks to find which worker is the closest
/// Using this will cause frame stutter, commenting out increases framerate
/// </summary>
/// <param name="currentPos">current position of the object checking</param>
sf::Vector2f Game::CheckForNearestWorker(sf::Vector2f currentPos)
{
	float currentAns = -1;
	float finalAns = 5000;
	sf::Vector2f finalPos;
	sf::Vector2f temp;
	for (size_t i = 0; i < workersEns.size(); i++)
	{
			temp = workersEns[i].getSprite().getPosition();
			currentAns = m_player->Magnitude(temp - currentPos);
			std::cout << currentAns << std::endl;
			if (currentAns < finalAns)
			{
				finalAns = currentAns;
				finalPos = temp;
				std::cout << temp.x << " " << temp.y << std::endl;
			}
		}
		return finalPos;
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (boids.size() < 2)
	{
		e3.setPosition(sf::Vector2f(playerView.getSize().x - (rand()%500),playerView.getSize().y-(rand() % 500)));
		boids.push_back(e3);
	}

	m_scorePreText.setPosition(sf::Vector2f(m_player->getPosition().x - 500, m_player->getPosition().y - 450));
	m_scoreText.setPosition(sf::Vector2f(m_scorePreText.getPosition().x + (m_scorePreText.getCharacterSize() * (m_scorePreText.getString().getSize()/1.5)), m_scorePreText.getPosition().y));
	std::stringstream sc;
	sc << score;
	m_scoreText.setString(sc.str().c_str());
	m_scorePreText.setString("Score: ");

	m_healthPreText.setPosition(m_scorePreText.getPosition().x, m_scorePreText.getPosition().y + 50);
	m_healthText.setPosition(m_healthPreText.getPosition().x + (m_healthPreText.getCharacterSize() * (m_healthPreText.getString().getSize()/1.5)), m_healthPreText.getPosition().y);
	std::stringstream hl;
	hl << m_player->getHealth();
	m_healthText.setString(hl.str().c_str());
	m_healthPreText.setString("Health: ");

	//View
	m_player->Update(centrePoint);

	//Player
	playerView.setCenter(m_player->getPosition());

	BulletHandler();
	EnemyHandler();
	WorkerHandler();
	



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
		for (size_t j = 0; j < enemies[i].getBullets().size(); j++)
		{
			m_window.draw(enemies[i].getBullets()[j].m_shape);
		}
		m_window.draw(enemies[i].getSprite());
	}

	for (size_t i = 0; i < boids.size(); i++)
	{
		//std::cout << nests[i].getPosition().x << " " << nests[i].getPosition().y << std::endl;
		m_window.draw(boids[i].getSprite());
	}

	for (size_t i = 0; i < nests.size(); i++)
	{
	//	std::cout << nests[i].getPosition().x << " " << nests[i].getPosition().y << std::endl;
		m_window.draw(nests[i]);
	}

	for (size_t i = 0; i < workersEns.size(); i++)
	{
		m_window.draw(workersEns[i].getSprite());
	}

	for (size_t i = 0; i < bullets.size(); i++)
	{
		m_window.draw(bullets[i].m_shape);
	}

	m_window.draw(m_player->getSprite());
	m_window.draw(m_scoreText);
	m_window.draw(m_scorePreText);
	m_window.draw(m_healthText);
	m_window.draw(m_healthPreText);

	m_window.display();
}



/// <summary>
/// load the textures and fonts,setup of sprites
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\Background.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setScale(sf::Vector2f(3.5, 3.5));
	m_logoSprite.setTexture(m_logoTexture);
	m_logoTexture.setRepeated(true);

	if (!m_scoreFont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	m_scorePreText.setFillColor(sf::Color::White);
	m_scorePreText.setFont(m_scoreFont);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setFont(m_scoreFont);

	m_healthPreText.setFillColor(sf::Color::White);
	m_healthPreText.setFont(m_scoreFont);
	m_healthText.setFillColor(sf::Color::White);
	m_healthText.setFont(m_scoreFont);

	if (!m_nestTexture.loadFromFile("ASSETS\\IMAGES\\nest.png"))
	{
		std::cout << "problem loading nest" << std::endl;
	}
	m_nestSprite.setTexture(m_nestTexture);
	m_nestSprite.setScale(sf::Vector2f(0.2, 0.2));
}
