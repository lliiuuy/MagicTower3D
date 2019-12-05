#include "RedKey.h"

RedKey::RedKey(Vector2* positionInMap): ConsumbleItem(positionInMap)
{
	this->redKeyNumber = 1;
	this->name = "RedKey";
}
