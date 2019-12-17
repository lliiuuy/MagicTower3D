#include "TheOrbOfTheHero.h"

void TheOrbOfTheHero::useItem()
{
}

void TheOrbOfTheHero::save()
{
}

void TheOrbOfTheHero::load()
{
}

TheOrbOfTheHero::TheOrbOfTheHero(Vector2* positionInMap): UseItem(positionInMap)
{
	this->name = "The orb of the hero";
	this->index = 0;
}
