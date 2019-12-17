#include "TheOrbOfWisdom.h"

void TheOrbOfWisdom::save()
{
}

void TheOrbOfWisdom::load()
{
}

void TheOrbOfWisdom::useItem()
{
}

TheOrbOfWisdom::TheOrbOfWisdom(Vector2* positionInMap): UseItem(positionInMap)
{
	this->name = "The orb of wisdom";
	this->messages = new std::vector<char*>();
	this->numberOfMessages = 0;
	this->index = 2;
}
