#include "IronSword.h"

IronSword::IronSword(Vector2* positionInMap): Sword(positionInMap)
{
	this->attack = 10;
	this->name = "Iron Sword";
	this->uiName = "Iron";
}
