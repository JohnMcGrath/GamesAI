#pragma once
#include "Game.h"

Enemy::Enemy() {}

void Enemy::HandleInput(sf::Vector2f t) {

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
	m_sprite.setPosition(sf::Vector2f(400, 100));
}

void Enemy::Update() {
	std::cout << m_position.x << std::endl;
	m_sprite.setPosition(m_position);

	m_velocity = Normalise(m_velocity);

	setPosition(m_position + (sf::Vector2f(getVelocity().x*m_maxSpeed, getVelocity().y*m_maxSpeed)));
}