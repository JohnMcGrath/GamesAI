
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
		m_nestSprite.setPosition(sf::Vector2f(rand() % m_window.getSize().x, rand() % m_window.getSize().y));
		m_nestSprite.setOrigin(sf::Vector2f(m_nestSprite.getPosition().x + (m_nestSprite.getGlobalBounds().width / 2), m_nestSprite.getPosition().y + (m_nestSprite.getGlobalBounds().height / 2)));
		nests.push_back(m_nestSprite);
	}

	if (spawnCounter >= 40 & enemies.size() < 5)
	{
		spawnCounter = 0;
		int tempNestPos = rand() % nests.size();
		e1.setPosition(sf::Vector2f(nests[tempNestPos].getPosition().x, nests[tempNestPos].getPosition().y));
		//e1.setPosition(sf::Vector2f(rand() % m_window.getSize().x, rand() % m_window.getSize().y));
		enemies.push_back(e1);
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].Update(m_player->getPosition(), centrePoint, 1);
	}
}
void Game::WorkerHandler()
{
	if (workerCounter < 40)
	{
		workerCounter++;
	}
	if (workerCounter >= 40 & workersEns.size() < 15)
	{
		std::cout << "Worker Spawned" << std::endl;
		workerCounter = 0;
		e2.setPosition(sf::Vector2f((rand() % -100 + 100) + m_player->getPosition().x, (rand() % -100 + 100) + m_player->getPosition().y));
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
			std::cout << "Bullet Removed" << std::endl;
			bullets.erase(bullets.begin() + i);
			break;
		}

		else
		{
			for (size_t k = 0; k < enemies.size(); k++)
			{
				bulletBound = bullets[i].m_shape.getGlobalBounds();
				bulletBoundShape.setSize(sf::Vector2f(bulletBound.width, bulletBound.height));
				bulletBoundShape.setPosition(sf::Vector2f(bulletBound.left, bulletBound.top));

				enemyBound = enemies[k].getSprite().getGlobalBounds();
				enemyBoundShap.setSize(sf::Vector2f(enemyBound.width, enemyBound.height));
				enemyBoundShap.setPosition(sf::Vector2f(enemyBound.left, enemyBound.top));

				if (bulletBoundShape.getGlobalBounds().intersects(enemyBoundShap.getGlobalBounds()))
				{
					bullets.erase(bullets.begin() + i);
					enemies.erase(enemies.begin() + k);
					break;
				}
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
	m_scorePreText.setPosition(sf::Vector2f(m_player->getPosition().x - 500, m_player->getPosition().y - 450));
	m_scoreText.setPosition(sf::Vector2f(m_scorePreText.getPosition().x + (m_scorePreText.getCharacterSize() * (m_scorePreText.getString().getSize()/1.5)), m_scorePreText.getPosition().y));
	std::stringstream sc;
	sc << score;
	m_scoreText.setString(sc.str().c_str());
	m_scorePreText.setString("Score: ");

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
		m_window.draw(enemies[i].getSprite());
	}

	for (size_t i = 0; i < nests.size(); i++)
	{
		//m_nestSprite.setPosition(sf::Vector2f(rand() % m_window.getSize().x, rand() % m_window.getSize().y));
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

	if (!m_nestTexture.loadFromFile("ASSETS\\IMAGES\\nest.png"))
	{
		std::cout << "problem loading nest" << std::endl;
	}
	m_nestSprite.setTexture(m_nestTexture);
	m_nestSprite.setScale(sf::Vector2f(0.2, 0.2));
}
