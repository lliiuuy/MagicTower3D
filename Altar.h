#pragma once
#include "NPC.h"

class Altar : // ��̳�����ڻ�Ǯ��������
	public NPC
{
private:
	unsigned int cost = 0; // ���ѵĽ�Ǯ��
	unsigned int health = 0; // ���ӵ�Ѫ��
	unsigned int attack = 0; // ���ӵĹ�����
	unsigned int defence = 0; // ���ӵķ�����

	unsigned short indexOfChoose = 0;

	char sentence[1000] = "";

	bool canBuy = false;

	bool loadTexture();

	void talk() { this->talking = true; }

public:
	unsigned int getCost() { return cost; }
	unsigned int getHealth() { return health; }
	unsigned int getAttack() { return attack; }
	unsigned int getDefence() { return defence; }

	void nextSentence()
	{
		if (indexOfMessages == 1)
		{
			if (canBuy)
			{
				talking = false;
				indexOfMessages = 0;
			}
			else
				indexOfMessages++;

		}
		else if (indexOfMessages + 1 >= numberofMessages)
		{
			indexOfMessages = 0;
			talking = false;
		}
		else
			indexOfMessages++;
	}

	void draw2D(int width, int height);
	void draw3D();
	std::string save();
	void load(std::string jsonString);
	void display(Vector3* position) {}

	Altar(Vector2* positionInMap);

	void setCanBuy(bool canBuy) { this->canBuy = canBuy; }

	unsigned short getIndexOfChoose() { return indexOfChoose; }
	void setIndexOfChoose(unsigned short index) { this->indexOfChoose = index; }

	char* getSentence() 
	{
		if (indexOfMessages == 0)
		{
			sprintf_s(sentence, "If you offer me %d Gold, I will#grant your request. Will you?", cost);
			return sentence;
		}
		else if (indexOfMessages == 1)
		{
			sprintf_s(sentence, "What option shall you choose?#Your life recovers by %d points#The offensive power is raised %d points.#The defensive power is raised %d points.#Then I won't do it after all.", health, attack, defence);
			return sentence;
		}
		else
			return messages->at(indexOfMessages)->getSentence();
	}
	char* getMessage() { return messages->at(indexOfMessages)->getMessage(); }
	bool isChoose() { return messages->at(indexOfMessages)->isChoose(); }
	bool isAction() { return messages->at(indexOfMessages)->isAction(); }
	bool isTalking() { return talking; }
};

