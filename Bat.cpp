#include "Bat.h"

Bat::Bat(Vector2* positionInMap) : Monster(positionInMap)
{
	this->health = 35;
	this->attack = 38;
	this->defence = 3;
	this->money = 3;
	this->name = "Bat";
}
