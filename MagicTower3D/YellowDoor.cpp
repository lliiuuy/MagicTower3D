#include "YellowDoor.h"

YellowDoor::YellowDoor(Vector2* positionInMap): Door(positionInMap)
{
	this->tag = Tag::yellowDoor;
	this->name = "YellowDoor";
}
