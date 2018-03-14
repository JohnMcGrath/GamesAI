#pragma once
#include "FuzzyLogicSets.h"


class FuzzyLogCharacter
{
public:
	std::string weight = "weight", height = "height", strength = "strength", charisma = "charisma", intelligance = "intelligence";

	std::string name  = "name";

	int health = 5;

	

	std::map<std::string, int> enemyData;

	void setCurrentSkill(std::string skill)
	{
		currentSkill = skill;
	}
	std::string getCurrentSkill()
	{
		return currentSkill;
	}

	void InititaliseValues()
	{
		//Add in initial values to map
		enemyData.insert(std::pair<std::string, int>(weight, rand() % 7));
		enemyData.insert(std::pair<std::string, int>(height, rand() % 7));
		enemyData.insert(std::pair<std::string, int>(strength, rand() % 7));
		enemyData.insert(std::pair<std::string, int>(charisma, rand() % 7));
		enemyData.insert(std::pair<std::string, int>(intelligance, rand() % 7));

		if ((playOrEnem == 0) || (playOrEnem % 2 == 0))
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

		if ((playOrEnem == 0) || (playOrEnem % 2 == 0))
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

	void checkHealth()
	{
		std::cout << std::endl;
		if (health >= 4)
		{
			std::cout << "The " << name << " feels fine" << std::endl;
		}
		else if (health >= 3)
		{
			std::cout << "The " << name << " feels a little weak" << std::endl;
		}
		else if (health >= 1)
		{
			std::cout << "The " << name << " is baddly wounded" << std::endl;
		}
		else
		{
			std::cout << "The " << name << " fell victims to their wounds and died" << std::endl;
		}
	}
	/*std::string getSkillName(int s)
	{
		if (s == 0)
			return "weight";

		else if (s==1)
			return "height";

		else if(s == 2)
			return "strenght";

	}*/

	FuzzyLogCharacter()
	{
		srand(time(NULL));
		InititaliseValues();
	}

	int playOrEnem = 0;
private:
	std::string currentSkill;
};
