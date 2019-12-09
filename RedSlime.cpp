#include "RedSlime.h"

RedSlime::RedSlime(Vector2* positionInMap) : Monster(positionInMap)
{
	this->health = 45;
	this->attack = 20;
	this->defence = 2;
	this->money = 2;
}
