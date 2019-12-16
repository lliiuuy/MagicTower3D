#include "Thief.h"

Thief::Thief(Vector2* positionInMap): NPC(positionInMap)
{
	this->name = "Thief";
}

void Thief::save()
{
}

void Thief::load()
{
}
