#pragma once
#include "UseItem.h"
class TheOrbOfFlying :
	public UseItem
{
private:
	unsigned short maxFloor;
public:
	void load();
	void save();
	void useItem();

	void setMaxFloor(unsigned short floor) { this->maxFloor = floor; }
	TheOrbOfFlying(Vector2* positionInMap);
};

