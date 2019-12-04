#include "OldMan.h"

OldMan::OldMan(Vector2* positionInMap): NPC(positionInMap)
{
	this->tag = Tag::oldMan;
	this->name = "OldMan";
}

void OldMan::talk()
{
}
