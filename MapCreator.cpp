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
				if (element == "")
				{
					objects[i][j] == NULL;
				}
				else
				{
					// ¶ÁÈ¡element
				}
			}
		}
		floor = mapValue["mapFloor"].asInt();
		sprintf_s(upDirection, mapValue["upPosition"]["direction"].asCString());
		upPosition->x = mapValue["upPosition"]["x"].asInt();
		upPosition->y = mapValue["upPosition"]["y"].asInt();
	}
}

bool MapCreator::createMap2D()
{
	for (unsigned short i = 0; i < mapHeight; i++)
	{
		for (unsigned short j = 0; j < mapWidth; j++)
		{
			objects[i][j]->draw2D();
		}
	}
}

bool MapCreator::createMap3D()
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			objects[i][j]->draw3D();
		}
	}
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
