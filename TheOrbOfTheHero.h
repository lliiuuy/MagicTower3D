#pragma once
#include "UseItem.h"

class TheOrbOfTheHero :
	public UseItem
{
public:
	void useItem();
	void save();
	void load();
	TheOrbOfTheHero(Vector2* positionInMap);
};

