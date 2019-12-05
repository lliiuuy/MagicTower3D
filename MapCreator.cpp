#include "MapCreator.h"

bool MapCreator::loadMap(char* fileName)
{
	return false;
}

bool MapCreator::createMap2D()
{
	return false;
}

bool MapCreator::createMap3D()
{
	return false;
}

void MapCreator::upStairs()
{
}

void MapCreator::downStairs()
{
}

MapCreator::MapCreator()
{
	downPosition = new Vector2(0, 0);
	upPosition = new Vector2(0, 0);
	floor = 0;
}
