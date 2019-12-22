#pragma once
#include "UseItem.h"
class TheOrbOfFlying :
	public UseItem
{
public:
	void useItem() 
	{ 
		this->isUsing = true; 
	}
	void closeItem() { this->isUsing = false; }

	TheOrbOfFlying(Vector2* positionInMap);
};

