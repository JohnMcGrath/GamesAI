#pragma once
#include "Game.h"

Player::Player() {}

void Player::HandleInput(sf::Event event) {
	if (sf::Event::KeyPressed == event.type) //user key press
	{
		if (sf::Keyboard::Up == event.key.code)
		{
			float temp = getVelocity().y - 1;
			setVelocity(sf::Vector2f(getVelocity().x, temp));
		}
		if (sf::Keyboard::Down == event.key.code)
		{
			float temp = getVelocity().y + 1;
			setVelocity(sf::Vector2f(getVelocity().x, temp));
		}
		if (sf::Keyboard::Left == event.key.code)
		{
			float temp = getVelocity().x - 1;
			setVelocity(sf::Vector2f(temp,getVelocity().y));
		}
		if (sf::Keyboard::Right == event.key.code)
		{
			float temp = getVelocity().x + 1;
			setVelocity(sf::Vector2f(temp, getVelocity().y));
		}
	}
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
	m_sprite.setPosition(sf::Vector2f(100, 100)); 
}

void Player::Update() {
	std::cout << m_position.x << std::endl;
	m_sprite.setPosition(m_position);

	m_velocity = Normalise(m_velocity);

	setPosition(m_position + (sf::Vector2f(getVelocity().x*m_maxSpeed,getVelocity().y*m_maxSpeed)));
}