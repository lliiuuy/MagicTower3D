#pragma once
#include "UseItem.h"
#include "Monster.h"

class TheOrbOfTheHero :
	public UseItem
{
private:

	std::vector<char*>* names;
	std::vector<unsigned int>* health;
	std::vector<unsigned int>* attack;
	std::vector<unsigned int>* defence;
	std::vector<unsigned int>* money;
	std::vector<GLuint>* textures;
	std::vector<int>* damages;

	unsigned int playerDefence;
	unsigned int playerAttack;

public:
	void useItem() { this->isUsing = true; }
	void closeItem() { this->isUsing = false; }
	TheOrbOfTheHero(Vector2* positionInMap);

	void addMonster(Monster* monster) 
	{
		bool isHave = false;
		for (int i = 0; i < (int)names->size(); i++)
		{
			if (strcmp(names->at(i), monster->getName()) == 0)
				isHave = true;
		}
		if (!isHave)
		{
			names->push_back(monster->getName());
			health->push_back(monster->getHealth());
			attack->push_back(monster->getAttack());
			defence->push_back(monster->getDefence());
			money->push_back(monster->getMoney());
			textures->push_back(monster->getTexture());
			if (playerAttack <= monster->getDefence())
				damages->push_back(-1);
			else if (monster->getAttack() <= playerDefence)
				damages->push_back(0);
			else
				damages->push_back(((monster->getHealth() / (playerAttack - monster->getDefence()))) * (monster->getAttack() - playerDefence));
		}
	}

	void clearMonster() 
	{ 
		names->clear();
		health->clear();
		attack->clear();
		defence->clear();
		money->clear();
		textures->clear();
		damages->clear();
	}
	
	void setPlayer(unsigned int playerAttack, unsigned int playerDefence)
	{
		this->playerDefence = playerDefence;
		this->playerAttack = playerAttack;
	}

	unsigned int getSize() { return names->size(); }
	char* getNameOfMonster(int index) { return names->at(index); }
	unsigned int getHealthOfMonster(int index) { return health->at(index); }
	unsigned int getMoneyOfMonster(int index) { return money->at(index); }
	unsigned int getDefenceOfMonster(int index) { return defence->at(index); }
	unsigned int getAttackOfMonster(int index) { return attack->at(index); }
	int getDamageOfMonster(int index) { return damages->at(index); }
	GLuint getTextureOfMonster(int index) { return textures->at(index); }
};

