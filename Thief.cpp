#include "Thief.h"

Thief::Thief(Vector2* positionInMap): NPC(positionInMap)
{
	this->name = "Thief";
}

std::string Thief::save()
{
	std::string jsonString;
	return jsonString;
}

void Thief::load(std::string jsonString)
{
}
