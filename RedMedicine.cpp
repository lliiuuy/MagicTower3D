#include "RedMedicine.h"

RedMedicine::RedMedicine(Vector2* positionInMap): ConsumbleItem(positionInMap)
{
	this->health = 50;
	this->name = "Red Medicine";
}
