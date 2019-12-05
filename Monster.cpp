#include "Monster.h"

void Monster::spin()
{

}

bool Monster::loadTexture()
{
	return false;
}

Monster::Monster(Vector2* positionInMap): Creature(positionInMap)
{
}

void Monster::collide()
{
}

void Monster::draw2D()
{
}

void Monster::draw3D()
{
}

bool Monster::init()
{
	return false;
}
