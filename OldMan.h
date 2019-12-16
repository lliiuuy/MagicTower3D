#pragma once
#include "NPC.h"
class OldMan :
	public NPC
{
public:
	OldMan(Vector2* positionInMap);
	void talk();
	void save();
	void load();
};
