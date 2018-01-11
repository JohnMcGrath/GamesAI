
#ifndef GAME
#define GAME

#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "math.h"
#include "Worker.h"
#include <vector>
#include <iostream>
#include <cstdlib>

class Player;
class Enemy;
class Projectile;
class Bullet;
class Worker;

static const float VIEW_HEIGHT = 1080.0f;

class Game
{
public:
	Player * m_player = new Player();

	//Enemy * m_arriveEnemy = new Enemy();
	//std::vector<Enemy*> enemies;
	Worker w1;
	std::vector<Worker> workers;

	Enemy e1;
	std::vector<Enemy> enemies;

	Enemy e2;
	std::vector<Enemy> workersEns;

	Bullet  b1;
	std::vector<Bullet> bullets;
	

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
	void EnemyHandler();
	void PlayerHandler();
	void WorkerHandler();
	void BulletHandler();

	sf::RenderWindow m_window; // main SFML window
	sf::View playerView;
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	sf::Vector2f centrePoint;

	sf::Vector2f playerCentre;
	sf::Vector2f cursorPos;
	sf::Vector2f aimDir;
	sf::Vector2f normalisedAimDir;

	int spawnCounter = 20;
	int workerCounter = 20;
	int bulletCounter = 10;

	sf::FloatRect bulletBound;
	sf::RectangleShape bulletBoundShape;
	sf::FloatRect enemyBound;
	sf::RectangleShape enemyBoundShap;
	sf::FloatRect workerBound;
	sf::RectangleShape workerBoundShape;
	sf::FloatRect playerBound;
	sf::RectangleShape playerBoundShap;
};

#endif // !GAME