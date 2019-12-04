#include "Sword.h"

Sword::Sword(Vector2* positionInMap): ConsumbleItem(positionInMap)
{
	this->tag = Tag::sword;
}
