#include "RedMedicine.h"

RedMedicine::RedMedicine(Vector2* positionInMap): ConsumbleItem(positionInMap)
{
	this->health = 50;
	this->tag = Tag::redMedicine;
	this->name = "RedMedicine";
}
