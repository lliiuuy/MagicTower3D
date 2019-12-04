#include "BlueMedicine.h"

BlueMedicine::BlueMedicine(Vector2* positionInMap): ConsumbleItem(positionInMap)
{
	this->health = 200;
	this->tag = Tag::blueMedicine;
	this->name = "BlueMedicine";
}
