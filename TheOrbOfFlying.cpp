#include "TheOrbOfFlying.h"

void TheOrbOfFlying::load()
{
}

void TheOrbOfFlying::save()
{
}

void TheOrbOfFlying::useItem()
{
}

TheOrbOfFlying::TheOrbOfFlying(Vector2* positionInMap): UseItem(positionInMap)
{
	this->name = "The orb of flying";
	this->index = 1;
	this->maxFloor = 1;
}
