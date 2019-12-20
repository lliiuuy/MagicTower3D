#include "SkeletonA.h"

SkeletonA::SkeletonA(Vector2* positionInMap): Boss(positionInMap)
{
	this->name = "SkeletonA";
	this->health = 100;
	this->attack = 65;
	this->defence = 15;
	this->money = 30;
}

void SkeletonA::load(std::string jsonString)
{
}

std::string SkeletonA::save()
{
	return std::string();
}
