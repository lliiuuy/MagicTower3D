#pragma once
#include "UseItem.h"

class TheOrbOfTheHero :
	public UseItem
{
public:
	void useItem();
	TheOrbOfTheHero(Vector2* positionInMap);
};

