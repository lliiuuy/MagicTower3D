#include "Priest.h"

Priest::Priest(Vector2* positionInMap) : Monster(positionInMap)
{
	this->health = 60;
	this->attack = 32;
	this->defence = 3;
	this->money = 5;
	this->name = "Priest";
}
