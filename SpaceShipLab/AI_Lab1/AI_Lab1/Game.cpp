
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
	
	playerView.setSize(sf::Vector2f(VIEW_HEIGHT,VIEW_HEIGHT));

	//Initialise the type of enemie that follows the player
	e1.Initialise(1);
	e2.Initialise(2);
	e3.Initialise(3);

	w1.Initialise();

	m_nestSprite.setPosition(sf::Vector2f(rand() % m_window.getSize().x, rand() % m_window.getSize().y));
	//std::cout << m_nestSprite.getPosition().x << " " << m_nestSprite.getPosition().y << std::endl;

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

void Game::EnemyHandler()
{
	if (spawnCounter < 40)
	{
		spawnCounter++;
	}

	if (nests.size() < 6)
	{
		m_nestSprite.setPosition(sf::Vector2f(rand() % 3200, rand() % 2500));
		m_nestSprite.setOrigin(m_nestSprite.getGlobalBounds().width, m_nestSprite.getGlobalBounds().height);
		nests.push_back(m_nestSprite);
	}

	if (spawnCounter >= 40 & enemies.size() < 5)
	{
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
			playerBound = m_player->getSprite().getGlobalBounds();
			playerBoundShap.setSize(sf::Vector2f(playerBound.width, playerBound.height));
			playerBoundShap.setPosition(sf::Vector2f(playerBound.left, playerBound.top));


			bulletBound = enemies[i].getBullets()[j].m_shape.getGlobalBounds();
			bulletBoundShape.setSize(sf::Vector2f(bulletBound.width, bulletBound.height));
			bulletBoundShape.setPosition(sf::Vector2f(bulletBound.left, bulletBound.top));

			if (playerBoundShap.getGlobalBounds().intersects(bulletBoundShape.getGlobalBounds()))
			{
				if (!m_player->getInvincible())
				{
					m_player->setInvincible(true);
					m_player->invinTimer = 0;
					m_player->setHealth(10);
					std::cout << "Player Health: " << m_player->getHealth() << std::endl;
				}
			}
		}
	}
	if (m_player->getInvincible())
	{
		m_player->invinTimer++;
	}
	if (m_player->invinTimer >= 100)
	{
		m_player->setInvincible(false);
	}
}
void Game::WorkerHandler()
{
	if (workersEns.size() < 15)
	{
		std::cout << "Worker Spawned" << std::endl;
		e2.setPosition(sf::Vector2f((rand() % -500 + 500) + m_player->getPosition().x, (rand() % -500 + 500) + m_player->getPosition().y));
		workersEns.push_back(e2);
	}

	for (size_t j = 0; j < workersEns.size(); j++)
	{
		workersEns[j].Update(m_player->getPosition(), centrePoint, 2);

		workerBound = workersEns[j].getSprite().getGlobalBounds();
		workerBoundShape.setSize(sf::Vector2f(workerBound.width, workerBound.height));
		workerBoundShape.setPosition(sf::Vector2f(workerBound.left, workerBound.top));

		playerBound = m_player->getSprite().getGlobalBounds();
		playerBoundShap.setSize(sf::Vector2f(playerBound.width, playerBound.height));
		playerBoundShap.setPosition(sf::Vector2f(playerBound.left, playerBound.top));

		if (workerBoundShape.getGlobalBounds().intersects(playerBoundShap.getGlobalBounds()))
		{
			workersEns.erase(workersEns.begin() + j);
			score++;
			break;
		}
	}
}

void Game::BulletHandler()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
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
	playerCentre = sf::Vector2f(m_player->getPosition());
	cursorPos = sf::Vector2f(10 * sin(m_player->getOrientation()) + m_player->getPosition().x, 10 * -cos(m_player->getOrientation()) + m_player->getPosition().y);
	aimDir = cursorPos - playerCentre;
	normalisedAimDir = m_player->Normalise(aimDir);

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].m_shape.move(bullets[i].m_velocity);

		if (m_player->Magnitude(bullets[i].m_shape.getPosition() - m_player->getPosition()) > 2000)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}

		else
		{
			bulletBound = bullets[i].m_shape.getGlobalBounds();
			bulletBoundShape.setSize(sf::Vector2f(bulletBound.width, bulletBound.height));
			bulletBoundShape.setPosition(sf::Vector2f(bulletBound.left, bulletBound.top));

			for (size_t k = 0; k < enemies.size(); k++)
			{
				enemyBound = enemies[k].getSprite().getGlobalBounds();
				enemyBoundShap.setSize(sf::Vector2f(enemyBound.width, enemyBound.height));
				enemyBoundShap.setPosition(sf::Vector2f(enemyBound.left, enemyBound.top));

				if (bulletBoundShape.getGlobalBounds().intersects(enemyBoundShap.getGlobalBounds()))
				{
					bullets.erase(bullets.begin() + i);
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

sf::Vector2f Game::CheckForNearestWorker(sf::Vector2f currentPos)
{
	float currentAns = -1;
	float finalAns = 5000;
	int pos = 0;
	for (size_t i = 0; i < workers.size(); i++)
	{
		currentAns = m_player->Magnitude(workers[i].getSprite().getPosition() - currentPos);
		if (currentAns < finalAns)
		{
			finalAns = currentAns;
			pos = i;
		}
	}
	return workers[pos].getPosition();
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

	for (size_t i = 0; i < nests.size(); i++)
	{
		std::cout << nests[i].getPosition().x << " " << nests[i].getPosition().y << std::endl;
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
/// load the texture and setup the sprite for the logo
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
