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
		downPosition->x = (float)mapValue["downPosition"]["x"].asInt();
		downPosition->y = (float)mapValue["downPosition"]["y"].asInt();
		for (unsigned short i = 0; i < mapHeight; i++)
		{
			for (unsigned short j = 0; j < mapWidth; j++)
			{
				if (i == 0 || j == 0 || i == mapHeight - 1 || j == mapWidth - 1)
				{
					objects[i][j] = new Wall(new Vector2((float)i - 1, (float)j - 1));
					objects[i][j]->init();
				}
				else
				{
					char element[100];
					sprintf_s(element, mapValue["mapData"][(i - 1) * (mapWidth-2) + j - 1]["element"].asCString());
					if (strcmp(element, "") == 0)
						objects[i][j] = NULL;
					else if (strcmp(element, "Wall") == 0)
						objects[i][j] = new Wall(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Yellow Door") == 0)
						objects[i][j] = new YellowDoor(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Green Slime") == 0)
						objects[i][j] = new GreenSlime(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Red Slime") == 0)
						objects[i][j] = new RedSlime(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Bat") == 0)
						objects[i][j] = new Bat(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Priest") == 0)
						objects[i][j] = new Priest(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "SkeletonC") == 0)
						objects[i][j] = new SkeletonC(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "SkeletonB") == 0)
						objects[i][j] = new SkeletonB(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Yellow Key") == 0)
						objects[i][j] = new YellowKey(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Blue Key") == 0)
						objects[i][j] = new BlueKey(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Red Key") == 0)
						objects[i][j] = new RedKey(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Red Medicine") == 0)
						objects[i][j] = new RedMedicine(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Blue Medicine") == 0)
						objects[i][j] = new BlueMedicine(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Red Jewel") == 0)
						objects[i][j] = new RedJewel(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Blue Jewel") == 0)
						objects[i][j] = new BlueJewel(new Vector2((float)i - 1, (float)j - 1));
				}
				if (objects[i][j] != NULL)
					objects[i][j]->init();
			}
		}
		floor = mapValue["mapFloor"].asInt();
		sprintf_s(upDirection, mapValue["upPosition"]["direction"].asCString());
		upPosition->x = (float)mapValue["upPosition"]["x"].asInt();
		upPosition->y = (float)mapValue["upPosition"]["y"].asInt();
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
	display();
	// 根据顺序画图，不然Blend属性会乱
	for (unsigned short i = 0; i < mapHeight; i++)
	{
		for (unsigned short j = 0; j < mapHeight; j++)
		{
			floors[i][j]->draw3D();
			cells[i][j]->draw3D();
		}
	}
	for (unsigned short i = 0; i < mapHeight; i++)
	{
		for (unsigned short j = 0; j < mapWidth; j++)
		{
			if (objects[i][j] != NULL)
			{
				if(objects[i][j]->getTag() == Tag::wall || objects[i][j]->getTag() == Tag::door || objects[i][j]->getTag() == Tag::ironDoor || objects[i][j]->getTag() == Tag::prison)
					objects[i][j]->draw3D();
			}
		}
	}
	for (unsigned short i = 0; i < mapHeight; i++)
	{
		for (unsigned short j = 0; j < mapWidth; j++)
		{
			if (objects[i][j] != NULL)
			{
				if (objects[i][j]->getTag() == Tag::monster || objects[i][j]->getTag() == Tag::consumbleItem)
					objects[i][j]->draw3D();
			}
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

void MapCreator::display()
{
	player->display();
	for (unsigned short i = 0; i < mapHeight; i++)
	{
		for (unsigned short j = 0; j < mapWidth; j++)
		{
			if (objects[i][j] != NULL)
			{
				if (objects[i][j]->getTag() == Tag::consumbleItem || objects[i][j]->getTag() == Tag::monster)
					objects[i][j]->lookAt(player->getPositon());
			}
		}
	}
}

MapCreator::MapCreator(Player *player)
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
			cells[i][j] = new Floor(new Vector2(i-1, j-1), false);
			cells[i][j]->init();
		}
	}
	this->player = player;
	player->init();
}
