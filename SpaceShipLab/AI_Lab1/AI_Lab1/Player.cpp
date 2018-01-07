#pragma once
#include "Game.h"

Player::Player() {}

void Player::steerPlayer(sf::Vector2f t)
{
	m_velocity = (m_position + t) - m_position;
	m_velocity = Normalise(m_velocity);
	m_velocity * m_maxSpeed;
}

float Player::orientate()
{
	std::cout << "Win";
	float l = Magnitude(m_velocity);
	if (l > 0)
	{
		std::cout << "Win";
		return ((atan2(m_velocity.x, -m_velocity.y)) * 180 / 3.142);
	}
	else
	{
		std::cout << "Lose";
		return m_orientation;
	}
}

void Player::HandleInput(sf::Event event) {
	if (sf::Event::KeyPressed == event.type) //user key press
	{
		if (sf::Keyboard::Up == event.key.code)
		{
			float x = sin(m_orientation);
			float y = -cos(m_orientation);

			steerPlayer(sf::Vector2f(x, y));
		}
		if (sf::Keyboard::Down == event.key.code)
		{

			float x = sin(m_orientation* (180 / 3.142));
			float y = -cos(m_orientation* (180 / 3.142));

			steerPlayer(sf::Vector2f(x,y));
		}
		if (sf::Keyboard::Left == event.key.code)
		{
			m_orientation -= 4 / (180 / 3.142);
		}
		if (sf::Keyboard::Right == event.key.code)
		{
			m_orientation += 4 / (180 / 3.142);
		}
		if (sf::Keyboard::Space == event.key.code)
		{
			m_velocity = sf::Vector2f(0,0);
		}
	}
}

float Player::Distance(sf::Vector2f t)
{
	return sqrt(((t.x - m_position.x)*(t.x - m_position.x)) + ((t.y - m_position.y)*(t.y - m_position.y)));
}

float Player::Magnitude(sf::Vector2f v)
{
	return sqrt((v.x*v.x) + (v.y*v.y));
}

sf::Vector2f Player::Normalise(sf::Vector2f v)
{
	float temp = Magnitude(v);
	if (temp > 0)
	{
		return sf::Vector2f((v.x / temp), (v.y / temp));
	}
	else
		return v;

}

void Player::Initialise() {
	std::cout << "Player Initialise Entered" << std::endl;

	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Player.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.25, 0.25));
	m_sprite.setPosition(sf::Vector2f(300, 300)); 
}

void Player::WrapAround(sf::Vector2f screenSize) 
{
	if (m_position.x + m_sprite.getLocalBounds().width <= 0)
	{
		m_position.x = screenSize.x - 1;
	}
	if (m_position.x  > screenSize.x)
	{
		m_position.x = -1 - m_sprite.getLocalBounds().width;
	}
	if (m_position.y + m_sprite.getLocalBounds().height <= 0)
	{
		m_position.y = screenSize.y - 1;
	}
	if (m_position.y  > screenSize.y)
	{
		m_position.y = -1 - m_sprite.getLocalBounds().height;
	}
}

void Player::Update(sf::Vector2f centrePoint) {
	//m_lastOrient = m_orientation - m_lastOrient;
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(m_position);
	WrapAround(centrePoint);
	m_sprite.setRotation(m_orientation * (180 / 3.14));

	m_velocity = Normalise(m_velocity);
	setPosition(m_position + (sf::Vector2f(getVelocity().x*m_maxSpeed,getVelocity().y*m_maxSpeed)));
}