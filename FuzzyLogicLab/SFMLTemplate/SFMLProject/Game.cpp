#include "Game.h"
#include <iostream>



Game::Game() :
	m_exitGame{false} //when true game will exit
{
}


Game::~Game()
{
}

void Game::setUpFuzzyLogChars(int numOfChars)
{
	for (size_t i = 0; i < numOfChars; i++)
	{
		protoCharacter.playOrEnem = i;
		protoCharacter.randomiseStats();
		characters.push_back(protoCharacter);
	}
}

void Game::beginStory()
{
	m_fuzFunc->getHighestValue(&characters.at(0));
	m_fuzFunc->getHighestValue(&characters.at(1));
}

void Game::run()
{
	setUpFuzzyLogChars(2);
	beginStory();
	m_fuzFunc->compareSkills(&characters.at(0), &characters.at(1));
	while (true)
	{

	}
}
