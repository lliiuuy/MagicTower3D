#include "TheMagicianSergeant.h"

TheMagicianSergeant::TheMagicianSergeant(Vector2* positionInMap): Monster(positionInMap)
{
	this->name = "The Magician Sergeant";
	this->health = 230;
	this->attack = 450;
	this->defence = 100;
	this->money = 100;
}
