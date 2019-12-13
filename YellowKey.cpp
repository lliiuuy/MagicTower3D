#include "YellowKey.h"

YellowKey::YellowKey(Vector2* positionInMap): ConsumbleItem(positionInMap)
{
	this->yellowKeyNumber = 1;
	this->name = "Yellow Key";
}
