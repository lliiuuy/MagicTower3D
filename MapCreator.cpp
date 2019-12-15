#include "MapCreator.h"

bool MapCreator::loadMap()
{
	bool status = false;
	Json::Reader reader;
	Json::Value mapValue;

	char fileName[20];
	sprintf_s(fileName, "Data/Map/%d.file", player->getFloor());

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
					else if (strcmp(element, "Blue Door") == 0)
						objects[i][j] = new BlueDoor(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Red Door") == 0)
						objects[i][j] = new RedDoor(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Iron Door") == 0)
						objects[i][j] = new IronDoor(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Prison") == 0)
						objects[i][j] = new Prison(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "UpStairs") == 0)
					{
						cells[i][j] = NULL;
						objects[i][j] = new UpStairs(new Vector2((float)i - 1, (float)j - 1));
					}
					else if (strcmp(element, "DownStairs") == 0)
					{
						floors[i][j] = NULL;
						objects[i][j] = new DownStairs(new Vector2((float)i - 1, (float)j - 1));
					}
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
					else if(strcmp(element, "Old Man") == 0)
						objects[i][j] = new OldMan(new Vector2((float)i - 1, (float)j - 1));
				}
				if (objects[i][j] != NULL)
					objects[i][j]->init();
			}
		}
		sprintf_s(upDirection, mapValue["upPosition"]["direction"].asCString());
		upPosition->x = (float)mapValue["upPosition"]["x"].asInt();
		upPosition->y = (float)mapValue["upPosition"]["y"].asInt();
	}
	return status;
}

bool MapCreator::createMap2D(int width, int height)
{
	bool status = false;
	glMatrixMode(GL_PROJECTION);						// 选择透视矩阵
	glLoadIdentity();									// 重设透视矩阵

	glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);   // 设置平行投影

	glMatrixMode(GL_MODELVIEW);							// 选择模型矩阵
	glLoadIdentity();									// 重新载入模型矩阵
	// 先画地板
	for (unsigned short i = 0; i < mapWidth; i++)
	{
		for (unsigned short j = 0; j < mapHeight; j++)
		{
			if (cells[i][j] == NULL)
				floors[i][j]->draw2D(width, height);
			else
				cells[i][j]->draw2D(width, height);
		}
	}

	for (unsigned short i = 0; i < mapHeight - 0; i++)
	{
		for (unsigned short j = 0; j < mapWidth - 0; j++)
		{
			if (objects[i][j] != NULL)
			{
				glEnable(GL_BLEND);
				if(objects[i][j]->getTag() == Tag::wall || objects[i][j]->getTag() == Tag::door)
					glDisable(GL_BLEND);
				objects[i][j]->draw2D(width, height);
				glDisable(GL_BLEND);
			}
		}
	}
	glMatrixMode(GL_PROJECTION);						// 选择透视矩阵
	glLoadIdentity();									// 重设透视矩阵

	gluPerspective(60.0f, width * 1.3f / height, 0.1f, 1000.0f); //	设置回透视投影

	glMatrixMode(GL_MODELVIEW);							// 选择模型矩阵
	glLoadIdentity();									// 重新载入模型矩阵

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
			if(floors[i][j] != NULL)
				floors[i][j]->draw3D();
			if(cells[i][j] != NULL)
				cells[i][j]->draw3D();
		}
	}
	// 绘制墙
	for (unsigned short i = 0; i < mapHeight; i++)
	{
		for (unsigned short j = 0; j < mapWidth; j++)
		{
			if (objects[i][j] != NULL)
			{
				if(objects[i][j]->getTag() == Tag::wall)
					objects[i][j]->draw3D();
			}
		}
	}

	// 绘制楼梯
	for (unsigned short i = 0; i < mapHeight; i++)
	{
		for (unsigned short j = 0; j < mapWidth; j++)
		{
			if (objects[i][j] != NULL)
			{
				if (objects[i][j]->getTag() == Tag::upStairs || objects[i][j]->getTag() == Tag::downStairs)
				{
					if (i > 0 && j > 0)
					{
						if (objects[i - 1][j] == NULL) // 左侧是空的
							objects[i][j]->lookAt(new Vector3(-1, 0, 0));
						else if (objects[i + 1][j] == NULL) // 右侧是空的
							objects[i][j]->lookAt(new Vector3(1, 0, 0));
						else if (objects[i][j + 1] == NULL) // 下面是空的
							objects[i][j]->lookAt(new Vector3(0, 1, 0));
						else if (objects[i][j - 1] == NULL) // 上面是空的
							objects[i][j]->lookAt(new Vector3(0, -1, 0));
					}
					objects[i][j]->draw3D();
				}
			}
		}
	}

	for (unsigned short i = 0; i < mapHeight; i++)
	{
		for (unsigned short j = 0; j < mapWidth; j++)
		{
			if (objects[i][j] != NULL)
			{
				if (objects[i][j]->getTag() == Tag::door || objects[i][j]->getTag() == Tag::ironDoor || objects[i][j]->getTag() == Tag::prison)
				{
					if (i > 0 && j > 0)
					{
						if (objects[i - 1][j] != NULL)
						{
							if(objects[i-1][j]->getTag() == Tag::wall)
								objects[i][j]->lookAt(player->getPositon());
						}
					}
					objects[i][j]->draw3D();
				}
			}
		}
	}
	for (unsigned short i = 0; i < mapHeight; i++)
	{
		for (unsigned short j = 0; j < mapWidth; j++)
		{
			if (objects[i][j] != NULL)
			{
				if (objects[i][j]->getTag() == Tag::NPC)
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
	player->upStairs();
	loadMap();
}

void MapCreator::downStairs()
{
	player->downStairs();
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
				if (objects[i][j]->getTag() == Tag::consumbleItem || objects[i][j]->getTag() == Tag::monster || objects[i][j]->getTag() == Tag::NPC)
					objects[i][j]->lookAt(player->getPositon());
			}
		}
	}
}

MapCreator::MapCreator(Player *player)
{
	downPosition = new Vector2(0, 0);
	upPosition = new Vector2(0, 0);
	for (unsigned short i = 0; i < 13; i++)
	{
		for (unsigned short j = 0; j < 13; j++)
		{
			floors[i][j] = new Floor(new Vector2((float)i-1, (float)j-1), true);
			floors[i][j]->init();
			cells[i][j] = new Floor(new Vector2((float)i-1, (float)j-1), false);
			cells[i][j]->init();
		}
	}
	this->player = player;
}
