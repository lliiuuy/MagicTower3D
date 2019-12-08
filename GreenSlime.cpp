#include "GreenSlime.h"

GreenSlime::GreenSlime(Vector2* positionInMap): Monster(positionInMap)
{
	this->health = 35;
	this->attack = 18;
	this->defence = 1;
	this->money = 1;
	this->name = "Green Slime";
	// ²âÊÔÓÃ
	this->position = new Vector3(0, 0, 1);
}
