#pragma once
#include "NPC.h"
class Thief :
	public NPC
{
public:
	Thief(Vector2* positionInMap);
	void talk() {}
	void save();
	void load();
};

