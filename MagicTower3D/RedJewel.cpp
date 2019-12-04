#include "RedJewel.h"

RedJewel::RedJewel(Vector2* positionInMap): ConsumbleItem(positionInMap)
{
	this->attack = 2;
	this->name = "RedJewel";
}
