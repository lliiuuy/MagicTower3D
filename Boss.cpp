#include "Boss.h"

void Boss::nextSentence()
{
}

Boss::Boss(Vector2* positionInMap): Monster(positionInMap)
{
	this->messages = new std::vector<Message*>();
}

void Boss::load(std::string jsonString)
{
}
