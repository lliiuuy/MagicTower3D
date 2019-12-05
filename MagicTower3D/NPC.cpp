#include "NPC.h"

void NPC::spin()
{
}

void NPC::collide()
{
}

void NPC::draw()
{
}

bool NPC::init()
{
	return false;
}

NPC::NPC(Vector2* positionInMap): Object(positionInMap)
{
	this->tag = Tag::NPC;
}
