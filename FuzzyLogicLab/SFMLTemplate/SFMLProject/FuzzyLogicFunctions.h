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
		highest = 0;
		std::cout << "The " << fuzChar->name << "'s best skill is their " << tempString << std::endl;
		fuzChar->setCurrentSkill(tempString);
		
	}
	void thirdAttack(FuzzyLogCharacter * c, FuzzyLogCharacter * e)
	{
		std::cout << std::endl;

		if (c->health - e->health >= 3 || c->health - e->health <= -3)
		{
			std::cout << "The " << e->name << " wasn't doing too well. The " << c->name << " stood triumphant and booted him to the head" << std::endl;
			e->health -= 5;
			e->checkHealth();
		}
		else if (c->health - e->health >= 1 || c->health - e->health <= -1)
		{
			std::cout << "The " << e->name << " was hurt but still standing. The " << c->name << " threw a savage headbutt, knocking both to the floor" << std::endl;
			e->health -= 5;
			c->health -= 5;
			e->checkHealth();
			c->checkHealth();
		}
		else
		{
			std::cout << "The " << e->name << " barely felt a thing. The " << c->name << " cowered, with a mighty right hook, the " << e->name << " clattered him, to the floor" << std::endl;
			c->health -= 5;
			c->checkHealth();
		}
	}

	//Initital part of the story
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

	void secondAttack(FuzzyLogCharacter* c, FuzzyLogCharacter* e)
	{
		std::cout << std::endl;

		if (c->getCurrentSkill() == "weight")
		{
			if (c->enemyData["weight"] - e->enemyData["strength"] > 4)
			{
				std::cout << "The " << e->name << " hit the wall with a monsterous thud" << std::endl;
				e->health -= 3;
				e->checkHealth();
			}
			else if (c->enemyData["weight"] - e->enemyData["strength"] >= 2)
			{
				std::cout << "The " << e->name << " hit the wall and took quite a bump" << std::endl;
				e->health -= 2;
				e->checkHealth();
			}
			else
			{
				std::cout << "The " << e->name << " barely flinched" << std::endl;
				e->health -= 1;
				e->checkHealth();
			}
		}
		else if (c->getCurrentSkill() == "height")
		{
			if (c->enemyData["height"] - e->enemyData["intelligence"] > 4)
			{
				std::cout << "The " << e->name << " was terrified and ran straight into a wall, hurting himself bad" << std::endl;
				e->health -= 3;
				e->checkHealth();
			}
			else if (c->enemyData["height"] - e->enemyData["intelligence"] >= 2)
			{
				std::cout << "The " << e->name << " walked backwards in fright and tripped, hitting his head" << std::endl;
				e->health -= 2;
				e->checkHealth();
			}
			else
			{
				std::cout << "The " << e->name << " was smart enough to see just cause he's tall, doesn't mean he's strong" << std::endl;
				e->checkHealth();
			}
		}
		else if (c->getCurrentSkill() == "strength")
		{
			if (c->enemyData["strength"] - e->enemyData["strength"] > 4)
			{
				std::cout << "The " << e->name << " took the brunt of the punch with his face" << std::endl;
				e->health -= 3;
				e->checkHealth();
			}
			else if (c->enemyData["strength"] - e->enemyData["strength"] >= 2)
			{
				std::cout << "The " << e->name << " got hit but hit the " << c->name << " just as hard" << std::endl;
				e->health -= 2;
				c->health -= 2;
				e->checkHealth();
				c->checkHealth();
			}
			else
			{
				std::cout << "The " << e->name << " was strong enough to grab his fist and barely got scratched" << std::endl;
				e->health -= 1;
				e->checkHealth();
			}
		}
		else if (c->getCurrentSkill() == "charisma")
		{
			if (c->enemyData["charisma"] - e->enemyData["intelligence"] > 4)
			{
				std::cout << "The " << e->name << " felt very safe with the " << c->name << "but then the "<< e->name << " was literally stabbed in the back"<< std::endl;
				e->health -= 4;
				e->checkHealth();
			}
			else if (c->enemyData["charisma"] - e->enemyData["intelligence"] >= 2)
			{
				std::cout << "The " << e->name << " felt a little calmed but felt uneasy. Suddenly " << c->name << " sucker punched him" << std::endl;
				e->health -= 2;
				e->checkHealth();
			}
			else
			{
				std::cout << "The " << e->name << " didn't fall for his obvious trap" << std::endl;
			}
		}
		else  //intelligence
		{
			if (c->enemyData["intelligence"] - e->enemyData["height"] > 4)
			{
				std::cout << "The " << e->name << " reached for the plank also but his stubby arms couldn't reach and was reward with a wallop of the plank " << c->name << "but then the " << e->name << " was literally stabbed in the back" << std::endl;
				e->health -= 4;
				e->checkHealth();
			}
			else if (c->enemyData["intelligence"] - e->enemyData["height"] >= 2)
			{
				std::cout << "The " << e->name << " caught the plank at the same time. Both men took face bashes of either end" << std::endl;
				e->health -= 2;
				e->checkHealth();
				c->health -= 2;
				e->checkHealth();
			}
			else
			{
				std::cout << "The " << e->name << " grabbed it with his long arms far before the " << c->name << " and walloped him for good measure" << std::endl;
			}
		}
	}

	//Compares their two currently chosen skills
	void compareSkills(FuzzyLogCharacter* p, FuzzyLogCharacter* e)
	{
		std::cout<<std::endl;

		int pSkillRate = p->enemyData[p->getCurrentSkill()];
		int eSkillRate = e->enemyData[e->getCurrentSkill()];

		if (pSkillRate > eSkillRate)
		{
			std::cout << "The Player used their " << p->getCurrentSkill() << " to ";
			if (pSkillRate - eSkillRate >= 4)
			{
				firstAttack(p);
				secondAttack(p, e);
				thirdAttack(p, e);
			}
			else if (pSkillRate - eSkillRate >= 2)
			{
				firstAttack(p);
				secondAttack(p, e);
				thirdAttack(p, e);
			}
			else
			{
				firstAttack(p);
				secondAttack(p, e);
				thirdAttack(p, e);
			}
		}

		else
		{
			std::cout << "The Enemy used their " << e->getCurrentSkill() << " to ";
			if (eSkillRate - pSkillRate >= 4)
			{
				firstAttack(e);
				secondAttack(e, p);
				thirdAttack(e, p);
			}
			else if (eSkillRate - pSkillRate >= 2)
			{
				firstAttack(e);
				secondAttack(e, p);
				thirdAttack(e, p);
			}
			else
			{
				firstAttack(e);
				secondAttack(e, p);
				thirdAttack(e, p);
			}
		}
	}

private:
	std::map<std::string, int>::iterator tempIt;
	int highest = 0;
	std::string tempString = "";
};