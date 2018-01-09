
#ifndef GAME
#define GAME

#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include <iostream>

class Player;
class Enemy;
class Projectile;

static const float VIEW_HEIGHT = 1080.0f;

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
	void ResizeView(const sf::RenderWindow& window, sf::View view);
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::View playerView;
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	sf::Vector2f centrePoint;
};

#endif // !GAME