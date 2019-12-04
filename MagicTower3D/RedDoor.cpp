#include "RedDoor.h"

RedDoor::RedDoor(Vector2* positionInMap):Door(positionInMap)
{
	this->tag = Tag::redDoor;
	this->name = "RedDoor";
}
