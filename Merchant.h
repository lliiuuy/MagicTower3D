#pragma once
#include "NPC.h"
class Merchant :
	public NPC
{
private:
	short yellowKeyNumber = 0;
	short blueKeyNumber = 0;
	short redKeyNumber = 0;
	short cost = 0;

	bool canBuy = false;

	void talk() { this->talking = true; }

public:
	Merchant(Vector2* positionInMap);
	std::string save();
	void load(std::string jsonString);

	void nextSentence()
	{
		if (indexOfMessages == 0)
		{
			if (canBuy)
				indexOfMessages += 2;
			else
				indexOfMessages = 1;
		}
		else if (indexOfMessages == 1)
		{
			talking = false;
			indexOfMessages = 0;
		}
		else if (indexOfMessages + 1 >= numberofMessages)
		{
			talking = false;
			endTalking = true;
		}
		else
			indexOfMessages++;
	}

	short getYellowKeyNumber() { return this->yellowKeyNumber; }
	short getBlueKeyNumber() { return this->blueKeyNumber; }
	short getRedKeyNumber() { return this->redKeyNumber; }
	short getCost() { return this->cost; }

	void setCanBuy(bool canBuy) { this->canBuy = canBuy; }
};

