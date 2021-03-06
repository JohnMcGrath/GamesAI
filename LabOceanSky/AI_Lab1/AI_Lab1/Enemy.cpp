#pragma once
#include "Game.h"

Enemy::Enemy() {}

void Enemy::HandleInput(sf::Vector2f t, int typeOfMovement) {
	if (typeOfMovement == 0) 
	{
		m_velocity = t - m_position;
		m_velocity = Normalise(m_velocity);
		m_velocity * m_maxSpeed;
	}

	if (typeOfMovement == 1)
	{
		float timeToTarget = 0.5f;
		m_velocity = t - m_position;


		m_velocity *= timeToTarget;
		float l = Magnitude(m_velocity);
		if (l > m_maxSpeed) {
			m_velocity = Normalise(m_velocity);
			m_velocity *= m_maxSpeed;
		}
	}

	if (typeOfMovement == 2)
	{
		float dist = 1000;
		float rad = 700;
		sf::Vector2f travelPoint = Normalise(m_velocity) * dist;
		travelPoint += m_position;

		float randAngle = (rand() % 10) * (3.142 / 180);
		sf::Vector2f newTravelPoint;
		newTravelPoint = sf::Vector2f((rad * sin(randAngle) + newTravelPoint.x), (rad * cos(randAngle) + newTravelPoint.y));

		m_velocity = newTravelPoint - m_position;
		m_velocity = Normalise(m_velocity);
		m_velocity * m_maxSpeed;
	}

	if (typeOfMovement == 3)
	{
		float dist = 1200;
		float rad = 400;
		sf::Vector2f travelPoint = Normalise(m_velocity) * dist;
		travelPoint += m_position;

		float randAngle = (rand() % 4) * (3.142 / 180);
		sf::Vector2f newTravelPoint;
		newTravelPoint = sf::Vector2f((rad * sin(randAngle) + newTravelPoint.x), (rad * cos(randAngle) + newTravelPoint.y));

		m_velocity = newTravelPoint - m_position;
		m_velocity = Normalise(m_velocity);
		m_velocity * 1.5f;
	}
}

float Enemy::orientate()
{
	float l = Magnitude(m_velocity);
	if (l > 0)
	{
		return ((atan2(m_velocity.x, -m_velocity.y)) * 180 / 3.142);
	}
	else
	{
		return m_orientation;
	}
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

void Enemy::Initialise(int color) {
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Enemy.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	if (color == 1) m_sprite.setColor(sf::Color::Red);
	if (color == 2) m_sprite.setColor(sf::Color::Blue);
	if (color == 3) m_sprite.setColor(sf::Color::Cyan);

	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.25, 0.25));
}

void Enemy::Update(sf::Vector2f t, sf::Vector2f screenSize, int typeOfMovement) {
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	WrapAround(screenSize);
	m_sprite.setPosition(m_position);
	m_orientation = orientate();
	m_sprite.setRotation(m_orientation);
	HandleInput(t, typeOfMovement);
	m_position = m_position += m_velocity;
}