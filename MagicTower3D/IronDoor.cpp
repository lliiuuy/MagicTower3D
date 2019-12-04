#include "IronDoor.h"

IronDoor::IronDoor(Vector2* positionInMap): Door(positionInMap)
{
	this->tag = Tag::ironDoor;
	this->name = "IronDoor";
}
