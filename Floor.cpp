#include "Floor.h"

bool Floor::loadTexture()
{
	return false;
}

Floor::Floor(Vector2* positionInMap): Object(positionInMap)
{
	this->tag = Tag::floor;
	this->name = "Floor";
}

void Floor::draw2D()
{
}

void Floor::draw3D()
{
}

bool Floor::init()
{
	return false;
}
