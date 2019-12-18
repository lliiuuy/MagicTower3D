#include "SkeletonA.h"

SkeletonA::SkeletonA(Vector2* positionInMap): Monster(positionInMap)
{
	this->name = "SkeletonA";
	this->health = 100;
	this->attack = 65;
	this->defence = 15;
	this->money = 30;
}
