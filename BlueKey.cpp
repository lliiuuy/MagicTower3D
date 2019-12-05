#include "BlueKey.h"

BlueKey::BlueKey(Vector2* positionInMap): ConsumbleItem(positionInMap)
{
	this->blueKeyNumber = 1;
	this->name = "BlueKey";
}
