#include "MapCreator.h"

bool MapCreator::loadMap()
{
	bool status = false;
	Json::Reader reader;
	Json::Value mapValue;

	char fileName[20];
	sprintf_s(fileName, "Data/Map/%d.file", floor);

	std::ifstream is(fileName, std::ios::binary);

	if (reader.parse(is, mapValue))
	{
		sprintf_s(downDirection, mapValue["downPosition"]["direction"].asCString());
		downPosition->x = mapValue["downPosition"]["x"].asInt();
		downPosition->y = mapValue["downPosition"]["y"].asInt();
		for (unsigned short i = 0; i < mapHeight; i++)
		{
			for (unsigned short j = 0; j < mapWidth; j++)
			{
				char element[100];
				sprintf_s(element, mapValue["mapData"][i * mapWidth + j]["element"].asCString());
				if (strcmp(element,"") == 0)
				{
					objects[i][j] = NULL;
				}
				else if(strcmp(element, "wall") == 0)
				{
					objects[i][j] = new Wall(new Vector2(i,j));
					objects[i][j]->init();
				}
			}
		}
		floor = mapValue["mapFloor"].asInt();
		sprintf_s(upDirection, mapValue["upPosition"]["direction"].asCString());
		upPosition->x = mapValue["upPosition"]["x"].asInt();
		upPosition->y = mapValue["upPosition"]["y"].asInt();
	}
	return status;
}

bool MapCreator::createMap2D()
{
	bool status = false;
	for (unsigned short i = 0; i < mapHeight; i++)
	{
		for (unsigned short j = 0; j < mapWidth; j++)
		{
			if (objects[i][j] != NULL)
				objects[i][j]->draw2D();
		}
	}
	return status;
}

bool MapCreator::createMap3D()
{
	bool status = false;
	//Floor* floor = new Floor(new Vector2(0, 0));
	//floor->draw3D();
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (objects[i][j] != NULL)
				objects[i][j]->draw3D();
		}
	}
	return status;
}

void MapCreator::upStairs()
{
	floor++;
	loadMap();
}

void MapCreator::downStairs()
{
	floor--;
	loadMap();
}

MapCreator::MapCreator()
{
	downPosition = new Vector2(0, 0);
	upPosition = new Vector2(0, 0);
	floor = 1;
}
