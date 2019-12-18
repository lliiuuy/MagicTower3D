#pragma once
#include "NPC.h"
class OldMan :
	public NPC
{
private:
	unsigned short indexOfUseItems = -1;
public:
	OldMan(Vector2* positionInMap);
	void talk();
	std::string save();
	void load(std::string jsonString);
	unsigned short getIndexOfUseItems() { return this->indexOfUseItems; }
};
