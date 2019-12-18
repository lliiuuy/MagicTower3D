#include "GateKeeperC.h"

GateKeeperC::GateKeeperC(Vector2* positionInMap): Monster(positionInMap)
{
	this->name = "Gate-Keeper C";
	this->health = 50;
	this->attack = 48;
	this->defence = 22;
	this->money = 15;
}
