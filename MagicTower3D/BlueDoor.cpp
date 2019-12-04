#include "BlueDoor.h"

BlueDoor::BlueDoor(Vector2* positionInMap): Door(positionInMap)
{
	this->tag = Tag::blueDoor;
	this->name = "BlueDoor";
}
