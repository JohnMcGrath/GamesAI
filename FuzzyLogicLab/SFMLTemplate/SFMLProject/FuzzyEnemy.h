#pragma once
#include "FuzzyLogicSets.h"
#include <stdlib.h>
#include <time.h>
#include <map>
#include <string>
#include <iostream>

class FuzzyLogCharacter
{
public:
	std::string weight = "weight", height = "height", strength = "strength", charisma = "charisma", intelligance = "intelligence";

	std::string name  = "name";

	std::map<std::string, int> enemyData;

	void InititaliseValues()
	{
		//Add in initial values to map
		enemyData.insert(std::pair<std::string, int>(weight, rand() % 7));
		enemyData.insert(std::pair<std::string, int>(height, rand() % 7));
		enemyData.insert(std::pair<std::string, int>(strength, rand() % 7));
		enemyData.insert(std::pair<std::string, int>(charisma, rand() % 7));
		enemyData.insert(std::pair<std::string, int>(intelligance, rand() % 7));

		//Randomise whether a player or enemy
		if (rand() % 2 == 1)
		{
			name = "Player";
		}

		else
		{
			name = "Enemy";
		}
	}

	void randomiseStats()
	{
		enemyData["weight"] = rand() % 7;
		enemyData["height"] = rand() % 7;
		enemyData["strength"] = rand() % 7;
		enemyData["charisma"] = rand() % 7;
		enemyData["intelligance"] = rand() % 7;

		if (rand() % 2 == 1)
		{
			name = "Player";
		}

		else
		{
			name = "Enemy";
		}

		outputStats();
	}

	void outputStats()
	{
		std::cout << name << " has a Weight of:" << enemyData["weight"] << std::endl;
		std::cout << name << " has a Height of:" << enemyData["height"] << std::endl;
		std::cout << name << " has a Strength of:" << enemyData["strength"] << std::endl;
		std::cout << name << " has a Charisma of:" << enemyData["charisma"] << std::endl;
		std::cout << name << " has an Intelligance of:" << enemyData["intelligance"] << std::endl << std::endl;
	}

	FuzzyLogCharacter()
	{
		srand(time(NULL));
		InititaliseValues();
	}

private:

};
