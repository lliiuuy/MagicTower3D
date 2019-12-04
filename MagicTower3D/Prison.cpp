#include "Prison.h"

Prison::Prison(Vector2* positionInMap): Door(positionInMap)
{
	this->tag = Tag::prison;
	this->name = "Prison";
}
