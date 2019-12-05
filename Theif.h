#pragma once
#include "NPC.h"
class Theif :
	public NPC
{
public:
	Theif(Vector2* positionInMap);
	void talk();
};

