#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Worker
{
public:
	Worker();
	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;
	float m_maxSpeed;



	void Initialise();

	sf::Texture getTexture() { return m_texture; }
	sf::Sprite getSprite() { return m_sprite; }
	sf::Vector2f getVelocity() { return m_velocity; }
	sf::Vector2f getPosition() { return m_position; }

	void setTexture(sf::Texture newTexture) { m_texture = newTexture; }
	void setSprite(sf::Sprite newSprite) { m_sprite = newSprite; }

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position = sf::Vector2f(500, 500);
};
