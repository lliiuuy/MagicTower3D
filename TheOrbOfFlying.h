#pragma once
#include "UseItem.h"
class TheOrbOfFlying :
	public UseItem
{
private:
	unsigned short maxFloor = 0;
public:
	void useItem() { this->isUsing = true; }
	void closeItem() { this->isUsing = false; }

	void load(std::string jsonString);
	std::string save();
	void setMaxFloor(unsigned short maxFloor) { this->maxFloor = maxFloor; }

	TheOrbOfFlying(Vector2* positionInMap);
};

