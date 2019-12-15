#include "GateKeeperB.h"

GateKeeperB::GateKeeperB(Vector2* positionInMap): Monster(positionInMap)
{
	this->name = "Gate-Keeper B";
	this->health = 100;
	this->attack = 180;
	this->defence = 110;
	this->money = 50;
}
