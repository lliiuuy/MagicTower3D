#include "UseItem.h"

bool UseItem::loadTexture()
{
	return false;
}

void UseItem::draw()
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
}
