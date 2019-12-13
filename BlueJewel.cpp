#include "BlueJewel.h"

BlueJewel::BlueJewel(Vector2* positionInMap): ConsumbleItem(positionInMap)
{
	this->defence = 2;
	this->name = "Blue Jewel";
}
