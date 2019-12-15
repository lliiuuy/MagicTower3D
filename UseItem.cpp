#include "UseItem.h"

bool UseItem::loadTexture()
{
	return false;
}

void UseItem::draw2D(int width, int height)
{
}

void UseItem::draw3D()
{
}

void UseItem::collide()
{
}

bool UseItem::init()
{
	return false;
}

UseItem::UseItem(Vector2* positionInMap): Object(positionInMap)
{
	this->tag = Tag::useItem;
	this->index = 0;
	this->enable = false;
}
