#include "Creature.h"

bool Creature::init()
{
	bool status;
	status = loadTexture();
	return status;
}

Creature::Creature(Vector2* positionInMap): Object(positionInMap)
{
}
