#pragma once
#include "UseItem.h"

class TheOrbOfTheHero :
	public UseItem
{
public:
	void useItem() { this->isUsing = true; }
	void closeItem() { this->isUsing = false; }
	std::string save();
	void load(std::string jsonString);
	TheOrbOfTheHero(Vector2* positionInMap);
};

