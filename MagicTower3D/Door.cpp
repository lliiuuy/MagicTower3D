#include "Door.h"

bool Door::loadTexture()
{
	return false;
}

void Door::draw()
{
}

void Door::open()
{
}

void Door::collide()
{
	open();
}

bool Door::init()
{
	return false;
}

Door::Door(Vector2* positionInMap): Object(positionInMap)
{
	this->tag = Tag::door;
}
