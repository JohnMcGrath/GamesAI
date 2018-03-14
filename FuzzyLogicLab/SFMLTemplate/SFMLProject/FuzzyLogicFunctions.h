#pragma once
#include "FuzzyEnemy.h"

class FuzzyLogicFunctions
{
public:
	void getHighestValue(FuzzyLogCharacter* fuzChar)
	{
		std::map<std::string, int>::iterator it;


		for (it = fuzChar->enemyData.begin(); it != fuzChar->enemyData.end(); it++)
		{
			if (it->second > highest)
			{
				highest = it->second;
				tempIt = it;
				tempString = tempIt->first;
			}
		}
		std::cout << "The " << fuzChar->name << "'s best skill is their " << tempString << std::endl;
		fuzChar->setCurrentSkill(tempString);
		//fuzChar->setCurrentSkill(tempString);
	}

	void firstAttack(FuzzyLogCharacter* c)
	{
		if (c->getCurrentSkill() == "weight")
		{
			std::cout << "push their foe against a nearby wall" << std::endl;
		}
		else if (c->getCurrentSkill() == "height")
		{
			std::cout << "intimidate their foe" << std::endl;
		}
		else if (c->getCurrentSkill() == "strength")
		{
			std::cout << "punch their foe" << std::endl;
		}
		else if (c->getCurrentSkill() == "charisma")
		{
			std::cout << "calm down their foe" << std::endl;
		}
		else  //intelligence
		{
			std::cout << "spot a loose wooden plank by the wall" << std::endl;
		}
	}

	void compareSkills(FuzzyLogCharacter* p, FuzzyLogCharacter* e)
	{
		int pSkillRate = p->enemyData[p->getCurrentSkill()];
		int eSkillRate = e->enemyData[e->getCurrentSkill()];

		if (pSkillRate > eSkillRate)
		{
			std::cout << "The Player used their " << p->getCurrentSkill() << "to ";
			if (pSkillRate - eSkillRate >= 4)
			{
				firstAttack(p);
			}
			else if (pSkillRate - eSkillRate >= 2)
			{
				firstAttack(p);
			}
			else
			{
				firstAttack(p);
			}
		}

		else
		{
			std::cout << "The Enemy used their " << e->getCurrentSkill() << " to ";
			if (eSkillRate - pSkillRate >= 4)
			{
				firstAttack(e);
			}
			else if (eSkillRate - pSkillRate >= 2)
			{
				firstAttack(e);
			}
			else
			{
				firstAttack(e);
			}
		}
	}
private:
	std::map<std::string, int>::iterator tempIt;
	int highest = 0;
	std::string tempString = "";
};