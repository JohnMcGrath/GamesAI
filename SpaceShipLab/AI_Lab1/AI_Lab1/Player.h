#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();

	void HandleInput();
	void Initialise();
	void Update(sf::Vector2f centrePoint);
	void setVelocity(sf::Vector2f newVelocity) { m_velocity = newVelocity; }
	void setPosition(sf::Vector2f newPosition) { m_position = newPosition; }
	void setOrientation(float newOrientation) { m_orientation = newOrientation; }

	void steerPlayer(sf::Vector2f);

	void WrapAround(sf::Vector2f screenSize);

	float Distance(sf::Vector2f t);
	float Magnitude(sf::Vector2f v);
	sf::Vector2f Normalise(sf::Vector2f v);

	float orientate();

	sf::Vector2f getVelocity() { return m_velocity; }
	sf::Vector2f getPosition() { return m_position; }
	float getOrientation() { return m_orientation; }

	void setTexture(sf::Texture newTexture) { m_texture = newTexture; }
	void setSprite(sf::Sprite newSprite) { m_sprite = newSprite; }

	sf::Texture getTexture() { return m_texture; }
	sf::Sprite getSprite() { return m_sprite; }

	int getHealth() { return m_health; }
	void setHealth(int h) { m_health -= h; }

	bool getInvincible() { return invincile; }
	void setInvincible(bool tf) { invincile = tf; }

	int invinTimer = 0;

private:
	sf::Vector2f tempVec;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position = sf::Vector2f(300, 300);
	float m_orientation = 0;
	float m_lastOrient = 0;

	float m_maxSpeed = 2.5f;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	int m_health = 100;

	bool invincile = false;
};
