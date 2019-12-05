#include "BlueMedicine.h"

BlueMedicine::BlueMedicine(Vector2* positionInMap): ConsumbleItem(positionInMap)
{
	this->health = 200;
	this->name = "BlueMedicine";
}
