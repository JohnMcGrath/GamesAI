// author Peter Lowe
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>

class Game
{
public:
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
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

	sf::RectangleShape rect;
	sf::Vector2f rectVelocity = sf::Vector2f(0,0);
	int rectMaxSpeed = 3;

	sf::CircleShape circ;
	sf::Vector2f circleVelocity = sf::Vector2f(0, 0);

	void seek(sf::RectangleShape user, sf::RectangleShape target)
	{
	}
};

#endif // !GAME

