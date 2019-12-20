#include "Boss.h"

Boss::Boss(Vector2* positionInMap): Monster(positionInMap)
{
	this->messages = new std::vector<Message*>();
	this->tag = Tag::boss;
}
