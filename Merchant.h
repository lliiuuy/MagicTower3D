#pragma once
#include "NPC.h"
class Merchant :
	public NPC
{
public:
	Merchant(Vector2* positionInMap);
	void talk() {}
	void save();
	void load();
};

