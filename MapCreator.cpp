#include "MapCreator.h"

void MapCreator::loadMap(int floor)
{
	Json::Reader reader;
	Json::Value mapValue;

	char fileName[100];
	sprintf_s(fileName, "Data/Map/%d.file", floor);

	std::ifstream is(fileName, std::ios::binary);

	for (unsigned short i = 0; i < 13; i++)
	{
		for (unsigned short j = 0; j < 13; j++)
		{
			floors[i][j] = new Floor(new Vector2((float)i - 1, (float)j - 1), true);
			floors[i][j]->init();
			cells[i][j] = new Floor(new Vector2((float)i - 1, (float)j - 1), false);
			cells[i][j]->init();
		}
	}

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
					else if (strcmp(element, "Broken Wall") == 0)
					{
						objects[i][j] = new Wall(new Vector2((float)i - 1, (float)j - 1));
						((Wall*)objects[i][j])->setBrokenWall();
					}
					else if (strcmp(element, "Yellow Door") == 0)
						objects[i][j] = new YellowDoor(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Blue Door") == 0)
						objects[i][j] = new BlueDoor(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Red Door") == 0)
						objects[i][j] = new RedDoor(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Iron Door") == 0)
					{
						objects[i][j] = new IronDoor(new Vector2((float)i - 1, (float)j - 1));
						std::string jsonString = mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1].toStyledString();
						((IronDoor*)objects[i][j])->load(jsonString);
					}
					else if (strcmp(element, "Prison") == 0)
					{
						objects[i][j] = new Prison(new Vector2((float)i - 1, (float)j - 1));
						std::string jsonString = mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1].toStyledString();
						((Prison*)objects[i][j])->load(jsonString);
					}
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
					// 怪物
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
					else if (strcmp(element, "SkeletonA") == 0)
						objects[i][j] = new SkeletonA(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Gate-Keeper C") == 0)
						objects[i][j] = new GateKeeperC(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Gate-Keeper B") == 0)
						objects[i][j] = new GateKeeperB(new Vector2((float)i - 1, (float)j - 1));
					// 道具
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
					else if (strcmp(element, "Iron Sword") == 0)
						objects[i][j] = new IronSword(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Iron Shield") == 0)
						objects[i][j] = new IronShield(new Vector2((float)i - 1, (float)j - 1));
					// NPC
					else if (strcmp(element, "Old Man") == 0)
					{
						objects[i][j] = new OldMan(new Vector2((float)i - 1, (float)j - 1));
						std::string jsonString = mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1].toStyledString();
						((OldMan*)objects[i][j])->load(jsonString);
					}
					else if (strcmp(element, "Merchant") == 0)
					{
						objects[i][j] = new Merchant(new Vector2((float)i - 1, (float)j - 1));
						std::string jsonString = mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1].toStyledString();
						((Merchant*)objects[i][j])->load(jsonString);
					}
					else if (strcmp(element, "Thief") == 0)
						objects[i][j] = new Thief(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Altar") == 0)
					{
						objects[i][j] = new Altar(new Vector2((float)i - 1, (float)j - 1));
						std::string jsonString = mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1].toStyledString();
						((Altar*)objects[i][j])->load(jsonString);
					}
					// 主动道具
					else if (strcmp(element, "The orb of the hero") == 0)
						objects[i][j] = new TheOrbOfTheHero(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "The orb of flying") == 0)
						objects[i][j] = new TheOrbOfFlying(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "The orb of wisdom") == 0)
						objects[i][j] = new TheOrbOfWisdom(new Vector2((float)i - 1, (float)j - 1));
				}
				if (objects[i][j] != NULL)
					objects[i][j]->init();
			}
		}
		sprintf_s(upDirection, mapValue["upPosition"]["direction"].asCString());
		upPosition->x = (float)mapValue["upPosition"]["x"].asInt();
		upPosition->y = (float)mapValue["upPosition"]["y"].asInt();
	}
}

void MapCreator::saveMap(int floor)
{
	Json::Reader reader;
	Json::Value mapValue;
	mapValue["downPosition"]["direction"] = downDirection;
	mapValue["downPosition"]["x"] = downPosition->x;
	mapValue["downPosition"]["y"] = downPosition->y;
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (i > 0 && i < 12 && j > 0 && j < 12)
			{
				if (objects[i][j] == NULL)
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "";
				else if (strcmp(objects[i][j]->getName(), "Merchant") == 0)
				{
					std::string jsonString = ((Merchant*)objects[i][j])->save();
					reader.parse(jsonString, mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]);
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "Merchant";
				}
				else if (strcmp(objects[i][j]->getName(), "Old Man") == 0)
				{
					std::string jsonString = ((OldMan*)objects[i][j])->save();
					reader.parse(jsonString, mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]);
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "Old Man";
				}
				else if (strcmp(objects[i][j]->getName(), "Altar") == 0)
				{
					std::string jsonString = ((Merchant*)objects[i][j])->save();
					reader.parse(jsonString, mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]);
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "Altar";
				}
				else
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = objects[i][j]->getName();
			}
		}
	}
	mapValue["upPosition"]["direction"] = upDirection;
	mapValue["upPosition"]["x"] = upPosition->x;
	mapValue["upPosition"]["y"] = upPosition->y;

	Json::StyledWriter writer;

	std::ofstream os;
	char fileName[20];
	sprintf_s(fileName, "Data/Map/%d.file", floor);
	os.open(fileName);
	os << writer.write(mapValue);
}

void MapCreator::createMap2D(int width, int height)
{
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
}

void MapCreator::createMap3D()
{
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
							objects[i][j]->display(new Vector3(-1, 0, 0));
						else if (objects[i + 1][j] == NULL) // 右侧是空的
							objects[i][j]->display(new Vector3(1, 0, 0));
						else if (objects[i][j + 1] == NULL) // 下面是空的
							objects[i][j]->display(new Vector3(0, 1, 0));
						else if (objects[i][j - 1] == NULL) // 上面是空的
							objects[i][j]->display(new Vector3(0, -1, 0));
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
				if (objects[i][j]->getTag() == Tag::door 
					|| objects[i][j]->getTag() == Tag::ironDoor 
					|| objects[i][j]->getTag() == Tag::prison)
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
				if (objects[i][j]->getTag() == Tag::monster
					|| objects[i][j]->getTag() == Tag::consumbleItem
					|| objects[i][j]->getTag() == Tag::useItem
					|| objects[i][j]->getTag() == Tag::sword 
					|| objects[i][j]->getTag() == Tag::shield)
					objects[i][j]->draw3D();
			}
		}
	}
}

void MapCreator::display(Vector3* position)
{
	for (unsigned short i = 0; i < mapHeight; i++)
	{
		for (unsigned short j = 0; j < mapWidth; j++)
		{
			if (objects[i][j] != NULL)
			{
				if (objects[i][j]->getTag() == Tag::consumbleItem
					|| objects[i][j]->getTag() == Tag::useItem
					|| objects[i][j]->getTag() == Tag::monster 
					|| objects[i][j]->getTag() == Tag::NPC
					|| objects[i][j]->getTag() == Tag::sword
					|| objects[i][j]->getTag() == Tag::shield
					|| objects[i][j]->getTag() == Tag::wall)
					objects[i][j]->display(position);
				else if (objects[i][j]->getTag() == Tag::door
					|| objects[i][j]->getTag() == Tag::ironDoor
					|| objects[i][j]->getTag() == Tag::prison)
				{
					if (i > 0)
					{
						if (objects[i - 1][j] != NULL)
						{
							if (objects[i - 1][j]->getTag() == Tag::wall)
								objects[i][j]->display(position);
						}
						if (objects[i][j]->getTag() == Tag::ironDoor && !((Door*)objects[i][j])->isOpen())
						{
							Vector2* guardPosition = ((IronDoor*)objects[i][j])->getGuardPosition();
							Vector2* otherGuardPosition = ((IronDoor*)objects[i][j])->getOtherGuardPosition();
							if (objects[(int)guardPosition->x + 1][(int)guardPosition->y + 1] == NULL && objects[(int)otherGuardPosition->x + 1][(int)otherGuardPosition->y + 1] == NULL)
								((Door*)objects[i][j])->collide();
						}
						else if(objects[i][j]->getTag() == Tag::prison && !((Door*)objects[i][j])->isOpen())
						{
							Vector2* guardPosition = ((Prison*)objects[i][j])->getGuardPosition();
							Vector2* otherGuardPosition = ((Prison*)objects[i][j])->getOtherGuardPosition();
							if (objects[(int)guardPosition->x + 1][(int)guardPosition->y + 1] == NULL && objects[(int)otherGuardPosition->x + 1][(int)otherGuardPosition->y + 1] == NULL)
								((Door*)objects[i][j])->collide();
						}
					}
				}
				if (objects[i][j]->isDestroy())
				{
					delete objects[i][j];
					objects[i][j] = NULL;
				}
			}
		}
	}
}

Vector2* MapCreator::getUpDirection()
{
	// (左(0, 1), 右(0, -1), 前(1, 0), 后(-1, 0))
	if (strcmp(upDirection, "up") == 0)
		return new Vector2(1, 0);
	else if (strcmp(upDirection, "down") == 0)
		return new Vector2(-1, 0);
	else if (strcmp(upDirection, "left") == 0)
		return new Vector2(0, 1);
	else if (strcmp(upDirection, "right") == 0)
		return new Vector2(0, -1);
	return NULL;
}

Vector2* MapCreator::getDownDirection()
{
	if (strcmp(downDirection, "up") == 0)
		return new Vector2(1, 0);
	else if (strcmp(downDirection, "down") == 0)
		return new Vector2(-1, 0);
	else if (strcmp(downDirection, "left") == 0)
		return new Vector2(0, 1);
	else if (strcmp(downDirection, "right") == 0)
		return new Vector2(0, -1);
	return NULL;
}

Object* MapCreator::getObject(int x, int y)
{
	Object* object = NULL;
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (objects[i][j] != NULL)
			{
				if ((int)floor(objects[i][j]->getPositionInMap()->x + 0.5f) == x && (int)floor(objects[i][j]->getPositionInMap()->y + 0.5f) == y)
					object = objects[i][j];
			}
		}
	}
	return object;
}

MapCreator::MapCreator()
{
	downPosition = new Vector2(0, 0);
	upPosition = new Vector2(0, 0);
	for (unsigned short i = 0; i < 13; i++)
	{
		for (unsigned short j = 0; j < 13; j++)
		{
			floors[i][j] = new Floor(new Vector2((float)i - 1, (float)j - 1), true);
			floors[i][j]->init();
			cells[i][j] = new Floor(new Vector2((float)i - 1, (float)j - 1), false);
			cells[i][j]->init();
		}
	}
}
