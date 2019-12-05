#include "Wall.h"

bool Wall::loadTexture()
{
	return false;
}

Wall::Wall(unsigned short status, Vector2* positionInMap): Object(positionInMap)
{
	this->status = status;
	this->name = "Wall";
	this->tag = Tag::wall;
}

void Wall::destroy()
{
}

void Wall::appear()
{
}

void Wall::collide()
{
}

void Wall::draw()
{
}

bool Wall::init()
{
	return false;
}
