
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
#include <sstream>

class Player;
class Enemy;
class Projectile;
class Bullet;
class Worker;

static const float VIEW_HEIGHT = 1080.0f;

class Game
{
public:
	//Pointer to the player object
	Player * m_player = new Player();

	//Blueprint for the Enemies that Spawn from Nests
	Enemy e1;
	std::vector<Enemy> enemies;

	//Blueprint for the Workers
	Enemy e2;
	std::vector<Enemy> workersEns;

	//Blueprint for the boids
	Enemy e3;
	std::vector<Enemy> boids;

	//Bullets used by entities
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

	//Handle Classes for game entities
	void EnemyHandler();
	void WorkerHandler();
	void BulletHandler();

	//Checks for the nearest worker object, causes frame stutter upon starting app if used
	sf::Vector2f CheckForNearestWorker(sf::Vector2f currentPos);

	// main SFML window
	sf::RenderWindow m_window; 
	//View that Follows the player
	sf::View playerView;

	// texture and sprite used for background
	sf::Texture m_logoTexture; 
	sf::Sprite m_logoSprite; 

	// control exiting game
	bool m_exitGame;

	//centre of screen
	sf::Vector2f centrePoint;

	sf::Texture m_nestTexture;
	sf::Sprite m_nestSprite;
	std::vector<sf::Sprite> nests;

	//Vectors used in calculationg where the player is aiming
	sf::Vector2f playerCentre;
	sf::Vector2f cursorPos;
	sf::Vector2f aimDir;
	sf::Vector2f normalisedAimDir;

	//Counters used on things that continuosly spawn
	int spawnCounter = 40;
	int workerCounter = 20;
	int bulletCounter = 10;

	//player's score
	int score = 0;

	//Floats and rectShapes used to represent bounding boxes
	//Using .getLocalBounds on objects in vector caused some issues
	//but this resolves them
	sf::FloatRect bulletBound;
	sf::RectangleShape bulletBoundShape;
	sf::FloatRect enemyBound;
	sf::RectangleShape enemyBoundShap;
	sf::FloatRect workerBound;
	sf::RectangleShape workerBoundShape;
	sf::FloatRect playerBound;
	sf::RectangleShape playerBoundShap;

	//Font used by all text
	sf::Font m_scoreFont;

	//Score UI Hud
	sf::Text m_scoreText;
	sf::Text m_scorePreText;

	//Health UI Hud
	sf::Text m_healthText;
	sf::Text m_healthPreText;

	int nestCounter = 0;
};

#endif // !GAME