#include "TheOrbOfTheHero.h"

TheOrbOfTheHero::TheOrbOfTheHero(Vector2* positionInMap): UseItem(positionInMap)
{
	this->name = "The orb of the hero";
	this->index = 0;
	this->names = new std::vector<char*>();
	this->health = new std::vector<unsigned int>();
	this->attack = new std::vector<unsigned int>();
	this->defence = new std::vector<unsigned int>();
	this->money = new std::vector<unsigned int>();
	this->damages = new std::vector<int>();
	this->textures = new std::vector<GLuint>();
	this->playerAttack = 0;
	this->playerDefence = 0;
}
