#include "Shield.h"

Shield::Shield(Vector2* positionInMap): ConsumbleItem(positionInMap)
{
	this->tag = Tag::shield;
}
