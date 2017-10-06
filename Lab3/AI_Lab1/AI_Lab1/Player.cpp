#pragma once
#include "Game.h"

Player::Player() {}

void Player::HandleInput(sf::Event event) {
	if (sf::Event::KeyPressed == event.type) //user key press
	{
		//SF Event in PhysObj.h may cause issues?
		std::cout << "Player Handling Entered" << std::endl;
		if (sf::Keyboard::Up == event.key.code)
		{
			std::cout << "Up Entered" << std::endl;
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

void Player::Initialise() {
	std::cout << "Player Initialise Entered" << std::endl;

	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Player.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(sf::Vector2f(100, 100)); 
}

void Player::Update() {
	std::cout << getPosition().x << std::endl;
	m_sprite.setPosition(getPosition());

	setPosition(getPosition() + getVelocity());
}