// author Peter Lowe
#ifndef GAME
#define GAME

//#include <SFML/Graphics.hpp>
#include "FuzzyLogicFunctions.h"
#include <vector>

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
	//void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	void setUpFuzzyLogChars(int numOfChars);

	void beginStory();

	//sf::RenderWindow m_window; // main SFML window
	//sf::Font m_ArialBlackfont; // font used by message
	//sf::Text m_welcomeMessage; // text used for message on screen
	//sf::Texture m_logoTexture; // texture used for sfml logo
	//sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

	FuzzyLogCharacter protoCharacter;
	std::vector<FuzzyLogCharacter> characters;

	FuzzyLogicFunctions* m_fuzFunc = new FuzzyLogicFunctions();


};

#endif // !GAME

