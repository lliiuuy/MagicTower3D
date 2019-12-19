#include "RedJewel.h"

RedJewel::RedJewel(Vector2* positionInMap): ConsumbleItem(positionInMap)
{
	this->attack = 1;
	this->name = "Red Jewel";
}
