#pragma once

#include "Game.h"
#include <iostream>

class PhysicsObject
{
public:
	sf::Event event;

	PhysicsObject();
	~PhysicsObject();

	void Update();
	void setVelocity(sf::Vector2f newVelocity) { m_velocity = newVelocity; }
	void setPosition(sf::Vector2f newPosition) { m_position = newPosition; }
	void setOrientation(sf::Vector2f newOrientation) { m_orientation = newOrientation; }

	sf::Vector2f getVelocity() { return m_velocity; }
	sf::Vector2f getPosition() { return m_position; }
	sf::Vector2f getOrientation() { return m_orientation; }

	void setTexture(sf::Texture newTexture) { m_texture = newTexture; }
	void setSprite(sf::Sprite newSprite) { m_sprite = newSprite; }

	sf::Texture getTexture() { return m_texture; }
	sf::Sprite getSprite() { return m_sprite; }


private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	sf::Vector2f m_orientation;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};