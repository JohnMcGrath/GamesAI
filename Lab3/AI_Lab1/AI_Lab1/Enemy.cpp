#pragma once
#include "Game.h"

Enemy::Enemy() {}

void Enemy::HandleInput(sf::Vector2f t) {
	std::cout << "Enemy Handler Entered" << std::endl;
	m_velocity = t - m_position;
	m_velocity = Normalise(m_velocity);
	m_velocity * m_maxSpeed;
}

void Enemy::WrapAround(sf::Vector2f screenSize)
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

float Enemy::Distance(sf::Vector2f t)
{
	return sqrt(((t.x - m_position.x)*(t.x - m_position.x)) + ((t.y - m_position.y)*(t.y - m_position.y)));
}

float Enemy::Magnitude(sf::Vector2f v)
{
	return sqrt((v.x*v.x) + (v.y*v.y));
}

sf::Vector2f Enemy::Normalise(sf::Vector2f v)
{
	float temp = Magnitude(v);
	if (temp > 0)
	{
		return sf::Vector2f((v.x / temp), (v.y / temp));
	}
	else
		return v;

}

void Enemy::Initialise() {
	std::cout << "Enemy Initialise Entered" << std::endl;

	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Enemy.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.25, 0.25));
}

void Enemy::Update(sf::Vector2f t, sf::Vector2f screenSize) {
	WrapAround(screenSize);
	m_sprite.setPosition(m_position);
	HandleInput(t);
	m_position = m_position += m_velocity;
}