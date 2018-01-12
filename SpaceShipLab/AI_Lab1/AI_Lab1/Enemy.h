#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"

class Bullet;

class Enemy
{
public:
	Bullet b;
	std::vector<Bullet> bullets;

	Enemy();



	void FireBullets(sf::Vector2f target);

	void HandleInput(sf::Vector2f t, int typeOfMovement);
	void Initialise(int color);
	void Update(sf::Vector2f t, sf::Vector2f screenSize, int typeOfMovement);

	void setVelocity(sf::Vector2f newVelocity) { m_velocity = newVelocity; }
	void setPosition(sf::Vector2f newPosition) { m_position = newPosition; }
	void setOrientation(float newOrientation) { m_orientation = newOrientation; }

	std::vector<Bullet> getBullets() { return bullets; }

	float orientate();
	void WrapAround(sf::Vector2f screenSize);

	float Magnitude(sf::Vector2f v);
	float Distance(sf::Vector2f t);
	sf::Vector2f Normalise(sf::Vector2f v);

	sf::Vector2f getVelocity() { return m_velocity; }
	sf::Vector2f getPosition() { return m_position; }
	float getOrientation() { return m_orientation; }

	void setTexture(sf::Texture newTexture) { m_texture = newTexture; }
	void setSprite(sf::Sprite newSprite) { m_sprite = newSprite; }

	sf::Texture getTexture() { return m_texture; }
	sf::Sprite getSprite() { return m_sprite; }

	sf::RectangleShape getCollisionBox();

private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_position = sf::Vector2f(500, 500);
	float m_orientation;
	float m_maxSpeed = 2.5f;

	sf::Texture m_texture;
	sf::Texture m_nestTexture;
	sf::Sprite m_sprite; 

	int timer = 40;
	sf::Vector2f newTravelPoint;
	float randAngle;

	sf::FloatRect enemyCol;
	sf::RectangleShape enemyColBox;

	int bulletCounter;
	sf::Vector2f enemyCentre;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNormal;
};