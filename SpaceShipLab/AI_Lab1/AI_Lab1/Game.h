
#ifndef GAME
#define GAME

#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include <iostream>

class Player;
class Enemy;
class Projectile;

class Game
{
public:
	Player * m_player = new Player();

	Projectile * temp = new Projectile();

	Enemy * m_arriveEnemy = new Enemy();

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