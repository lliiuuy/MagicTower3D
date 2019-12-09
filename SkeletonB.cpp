#include "SkeletonB.h"

SkeletonB::SkeletonB(Vector2* positionInMap) : Monster(positionInMap)
{
	this->health = 55;
	this->attack = 52;
	this->defence = 12;
	this->money = 8;
	this->name = "SkeletonB";
}
