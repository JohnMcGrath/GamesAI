// author Peter Lowe

#include "Game.h"
#include <iostream>
#include "math.h"



Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
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
			if (sf::Keyboard::Up == event.key.code)
			{
				rectVelocityY--;
			}
			if (sf::Keyboard::Down == event.key.code)
			{
				rectVelocityY++;
			}
			if (sf::Keyboard::Left == event.key.code)
			{
				rectVelocityX--;
			}
			if (sf::Keyboard::Right == event.key.code)
			{
				rectVelocityX++;
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
	rect.setPosition(sf::Vector2f(rect.getPosition().x + rectVelocityX, rect.getPosition().y + rectVelocityY));
	circ.setPosition(sf::Vector2f(circ.getPosition().x + circVelocityX, circ.getPosition().y + circVelocityY));

	if (circ.getPosition().x > m_window.getSize().x)
	{
		circ.setPosition(sf::Vector2f(0 - circ.getGlobalBounds().width, circ.getPosition().y));
	}

	if (circ.getPosition().y > m_window.getSize().y)
	{
		circ.setPosition(sf::Vector2f(circ.getPosition().x, 0 - circ.getGlobalBounds().height));
	}

	int x2_x1 = (m_window.getSize().x / 2) - rect.getPosition().x;
	int y2_y1 = (m_window.getSize().y / 2) - rect.getPosition().y;

	int temp = sqrt((x2_x1*x2_x1) + (y2_y1*y2_y1));
	std::cout << temp << std::endl;

	if (rectVelocityX > rectMaxSpeed)
	{
		rectVelocityX = rectMaxSpeed;
	}
	else if (rectVelocityX < -rectMaxSpeed)
	{
		rectVelocityX = -rectMaxSpeed;
	}
	if (rectVelocityY > rectMaxSpeed)
	{
		rectVelocityY = rectMaxSpeed;
	}
	else if (rectVelocityY < -rectMaxSpeed)
	{
		rectVelocityY = -rectMaxSpeed;
	}

	if (sqrt((x2_x1*x2_x1) + (y2_y1*y2_y1))>600)
	{
		rectVelocityX = -rectVelocityX;
		rectVelocityY = -rectVelocityY;
	}


	/*if (rect.getPosition().x > m_window.getSize().x)
	{
		rect.setPosition(sf::Vector2f(0, rect.getPosition().y));
		std::cout << "TTTTTTT" << std::endl;
	}
	
	if (rect.getPosition().x < 0)
	{
		rect.setPosition(sf::Vector2f(m_window.getSize().x, rect.getPosition().y));
		std::cout << "TTTTTTT" << std::endl;
	}

	if (rect.getPosition().y > m_window.getSize().y)
	{
		rect.setPosition(sf::Vector2f(rect.getPosition().x, 0));
		std::cout << "Reset to top" << std::endl;
	}
	if (rect.getPosition().y < 0)
	{
		rect.setPosition(sf::Vector2f(rect.getPosition().y, m_window.getSize().y));
		std::cout << "TTTTTTT" << std::endl;
	}*/

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
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_logoSprite);
	m_window.draw(circ);
	m_window.draw(rect);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);

	rect.setFillColor(sf::Color::Red);
	rect.setSize(sf::Vector2f(50, 50));
	rect.setPosition(30, 30);

	circ.setFillColor(sf::Color::Blue);
	circ.setRadius(25);
	circ.setPosition(100, 30);
}
