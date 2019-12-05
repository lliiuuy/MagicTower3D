#include "Altar.h"

bool Altar::loadTexture()
{
	return false;
}

bool Altar::init()
{
	return false;
}

void Altar::draw()
{
}

void Altar::collide()
{
}

Altar::Altar(Vector2* positionInMap): Object(positionInMap)
{
	this->name = "Altar";
}
