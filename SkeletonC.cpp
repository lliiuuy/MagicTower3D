#include "SkeletonC.h"

SkeletonC::SkeletonC(Vector2* positionInMap):Monster(positionInMap)
{
	this->health = 50;
	this->attack = 42;
	this->defence = 6;
	this->money = 6;
	this->name = "SkeletonC"; // �Һ����²����������x
}
