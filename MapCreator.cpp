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
				if (i == 0 || j == 0 || i == mapHeight - 1 || j == mapWidth - 1)
				{
					objects[i][j] = new Wall(new Vector2(i - 1, j - 1));
					objects[i][j]->init();
				}
				else
				{
					char element[100];
					sprintf_s(element, mapValue["mapData"][(i - 1) * (mapWidth-2) + j - 1]["element"].asCString());
					if (strcmp(element, "") == 0)
						objects[i][j] = NULL;
					else if (strcmp(element, "Wall") == 0)
						objects[i][j] = new Wall(new Vector2(i - 1, j - 1));
					else if (strcmp(element, "Yellow Door") == 0)
						objects[i][j] = new YellowDoor(new Vector2(i - 1, j - 1));
					else if(strcmp(element, "Green Slime") == 0)
						objects[i][j] = new GreenSlime(new Vector2(i - 1, j - 1));
				}
				if (objects[i][j] != NULL)
					objects[i][j]->init();
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
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (objects[i][j] != NULL)
				objects[i][j]->draw3D();
			floors[i][j]->draw3D();
			//cells[i][j]->draw3D();
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
	for (unsigned short i = 0; i < 13; i++)
	{
		for (unsigned short j = 0; j < 13; j++)
		{
			floors[i][j] = new Floor(new Vector2(i-1, j-1), true);
			floors[i][j]->init();
			/*cells[i][j] = new Floor(new Vector2(i, j), false);
			cells[i][j]->init();*/
		}
	}
}
