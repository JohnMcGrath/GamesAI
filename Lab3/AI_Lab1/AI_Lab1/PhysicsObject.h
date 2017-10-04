#pragma once

#include "Game.h"

class PhysicsObject
{
public:
	PhysicsObject();
	~PhysicsObject();

	void setVelocity(sf::Vector2f newVelocity) { m_velocity = newVelocity; }
	void setPosition(sf::Vector2f newPosition) { m_position = newPosition; }
	void setOrientation(sf::Vector2f newOrientation) { m_orientation = newOrientation; }

private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	sf::Vector2f m_orientation;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};