#include "MapCreator.h"

void MapCreator::loadMap(int floor, int maxFloor)
{
	Json::Reader reader;
	Json::Value mapValue;

	char fileName[100];
	if (floor <= maxFloor)
		sprintf_s(fileName, "Data/Map/%d.file", floor);
	else
		sprintf_s(fileName, "Data/MapOrigin/%d.file", floor);

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
						if (floor == 10)
						{
							if (i == 7 && j == 6)
								((IronDoor*)objects[i][j])->setClose(true);
							else if(i == 3 && j == 6)
								((IronDoor*)objects[i][j])->setClose(true);
						}
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
					// ����
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
					else if (strcmp(element, "Gate-Keeper C") == 0)
						objects[i][j] = new GateKeeperC(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "Gate-Keeper B") == 0)
						objects[i][j] = new GateKeeperB(new Vector2((float)i - 1, (float)j - 1));
					else if (strcmp(element, "The Magician Sergeant") == 0)
					{
						objects[i][j] = new TheMagicianSergeant(new Vector2((float)i - 1, (float)j - 1));
						if (floor == 3)
							((TheMagicianSergeant*)objects[i][j])->setAppear();
					}
					// boss
					else if (strcmp(element, "SkeletonA") == 0)
					{
						objects[i][j] = new SkeletonA(new Vector2((float)i - 1, (float)j - 1));
						std::string jsonString = mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1].toStyledString();
						((SkeletonA*)objects[i][j])->load(jsonString);
					}
					else if (strcmp(element, "The Magic Sergeant") == 0)
					{
						objects[i][j] = new TheMagicSergeant(new Vector2((float)i - 1, (float)j - 1));
						std::string jsonString = mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1].toStyledString();
						((TheMagicSergeant*)objects[i][j])->load(jsonString);
						if (floor == 3)
							((TheMagicSergeant*)objects[i][j])->setAppear();
					}
					// ����
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
					{
						objects[i][j] = new Thief(new Vector2((float)i - 1, (float)j - 1));
						std::string jsonString = mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1].toStyledString();
						((Thief*)objects[i][j])->load(jsonString);
					}
					else if (strcmp(element, "Altar") == 0)
					{
						objects[i][j] = new Altar(new Vector2((float)i - 1, (float)j - 1));
						std::string jsonString = mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1].toStyledString();
						((Altar*)objects[i][j])->load(jsonString);
					}
					// ��������
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
				Object* object = getObject(i - 1, j - 1);
				if (object == NULL)
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "";
				else if (strcmp(object->getName(), "Merchant") == 0)
				{
					std::string jsonString = ((Merchant*)object)->save();
					reader.parse(jsonString, mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]);
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "Merchant";
				}
				else if (strcmp(object->getName(), "Old Man") == 0)
				{
					std::string jsonString = ((OldMan*)object)->save();
					reader.parse(jsonString, mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]);
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "Old Man";
				}
				else if (strcmp(object->getName(), "Altar") == 0)
				{
					std::string jsonString = ((Merchant*)object)->save();
					reader.parse(jsonString, mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]);
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "Altar";
				}
				else if (strcmp(object->getName(), "Thief") == 0)
				{
					std::string jsonString = ((Thief*)object)->save();
					reader.parse(jsonString, mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]);
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "Thief";
				}
				// Boss
				else if (strcmp(object->getName(), "The Magic Sergeant") == 0)
				{
					std::string jsonString = ((TheMagicSergeant*)object)->save();
					reader.parse(jsonString, mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]);
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "The Magic Sergeant";
				}
				else if (strcmp(object->getName(), "SkeletonA") == 0)
				{
					std::string jsonString = ((SkeletonA*)object)->save();
					reader.parse(jsonString, mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]);
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "SkeletonA";
				}
				else if (object->getTag() == Tag::wall)
				{
					if (((Wall*)object)->isBrokenWall())
						mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "Broken Wall";
					else if(((Wall*)object)->isAppearWall())
						mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = "Appear Wall";
					else
						mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = object->getName();
				}
				else
					mapValue["mapData"][(i - 1) * (mapWidth - 2) + j - 1]["element"] = object->getName();
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
	// �Ȼ��ذ�
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
	// ����˳��ͼ����ȻBlend���Ի���
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
	// ����ǽ
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

	// ����¥��
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
						if (objects[i - 1][j] == NULL) // ����ǿյ�
							objects[i][j]->display(new Vector3(-1, 0, 0));
						else if (objects[i + 1][j] == NULL) // �Ҳ��ǿյ�
							objects[i][j]->display(new Vector3(1, 0, 0));
						else if (objects[i][j + 1] == NULL) // �����ǿյ�
							objects[i][j]->display(new Vector3(0, 1, 0));
						else if (objects[i][j - 1] == NULL) // �����ǿյ�
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
					|| objects[i][j]->getTag() == Tag::boss
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
					|| objects[i][j]->getTag() == Tag::boss
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
								((IronDoor*)objects[i][j])->openDoor(true);
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
					if (strcmp(objects[i][j]->getName(), "SkeletonA") == 0)
					{
						if (((Boss*)objects[i][j])->getIndexOfMessage() == 3)
						{
							delete objects[i][j];
							objects[i][j] = NULL;
						}
					}
					else
					{
						delete objects[i][j];
						objects[i][j] = NULL;
					}
				}
			}
		}
	}
}

Vector2* MapCreator::getUpDirection()
{
	// (��(0, 1), ��(0, -1), ǰ(1, 0), ��(-1, 0))
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
