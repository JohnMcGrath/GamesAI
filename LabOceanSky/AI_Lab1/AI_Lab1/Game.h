// author Peter Lowe
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "PhysicsObject.h"
#include <iostream>


class Enemy
{
public:
	Enemy();
	~Enemy();

	//sf::Event event;



	void HandleInput(sf::Vector2f t, int typeOfMovement);
	void Initialise(int color);
	void Update(sf::Vector2f t, sf::Vector2f screenSize, int typeOfMovement);

	void setVelocity(sf::Vector2f newVelocity) { m_velocity = newVelocity; }
	void setPosition(sf::Vector2f newPosition) { m_position = newPosition; }
	void setOrientation(float newOrientation) { m_orientation = newOrientation; }

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

private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_position = sf::Vector2f(500,500);
	float m_orientation;
	float m_maxSpeed = 2.5f;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};


class Player
{
public:
	Player();
	~Player();

	//sf::Event event;



	void HandleInput(sf::Event);
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

private:
	sf::Vector2f tempVec;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position = sf::Vector2f(300,300);
	float m_orientation = 0;
	float m_lastOrient = 0;

	float m_maxSpeed = 2.5f;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

class Game
{

public:

	Player * m_player = new Player;

	Enemy * m_seekEnemy = new Enemy;
	Enemy * m_arriveEnemy = new Enemy;
	Enemy * m_wanderEnemy = new Enemy;
	Enemy * m_otherWanderEnemy = new Enemy;

	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	sf::Vector2f centrePoint;

};

#endif // !GAME

