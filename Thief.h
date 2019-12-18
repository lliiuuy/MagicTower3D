#pragma once
#include "NPC.h"
class Thief :
	public NPC
{
public:
	Thief(Vector2* positionInMap);
	void talk() {}
	std::string save();
	void load(std::string jsonString);
};

