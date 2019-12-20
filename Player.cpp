#include "Player.h"

bool Player::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[4];

	memset(textureImage, 0, sizeof(void*) * 4);

	char fileName[100];
	sprintf_s(fileName, "Data/Creature/Player/Battle.bmp");
	if (textureImage[0] = loadBMP(fileName))
	{
		glGenTextures(1, &battleTexture[0]);
		glBindTexture(GL_TEXTURE_2D, battleTexture[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[0]->sizeX, textureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[0]->data);
		if (textureImage[0])
		{
			if (textureImage[0]->data)
			{
				free(textureImage[0]->data);
			}
			free(textureImage[0]);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(i == 0)
				sprintf_s(fileName, "Data/Creature/Player/Left/%d.bmp", j + 1);
			else if(i == 1)
				sprintf_s(fileName, "Data/Creature/Player/Right/%d.bmp", j + 1);
			else if(i == 2)
				sprintf_s(fileName, "Data/Creature/Player/Up/%d.bmp", j + 1);
			else if(i == 3)
				sprintf_s(fileName, "Data/Creature/Player/Down/%d.bmp", j + 1);
			if (textureImage[j] = loadBMP(fileName))
			{
				status = true;
				if (i == 0)
				{
					glGenTextures(1, &left[j]);
					glBindTexture(GL_TEXTURE_2D, left[j]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
				}
				else if (i == 1)
				{
					glGenTextures(1, &right[j]);
					glBindTexture(GL_TEXTURE_2D, right[j]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
				}
				else if (i == 2)
				{
					glGenTextures(1, &up[j]);
					glBindTexture(GL_TEXTURE_2D, up[j]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
				}
				else if (i == 3)
				{
					glGenTextures(1, &down[j]);
					glBindTexture(GL_TEXTURE_2D, down[j]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
				}
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[j]->sizeX, textureImage[j]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[j]->data);
			}

			if (textureImage[j])
			{
				if (textureImage[j]->data)
				{
					free(textureImage[j]->data);
				}
				free(textureImage[j]);
			}
		}
	}

	sprintf_s(fileName, "Data/ConsumbleItem/Sword/Sacred Sword.bmp");
	if (textureImage[0] = loadBMP(fileName))
	{
		glGenTextures(1, &swordTexture);
		glBindTexture(GL_TEXTURE_2D, swordTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[0]->sizeX, textureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[0]->data);
		if (textureImage[0])
		{
			if (textureImage[0]->data)
			{
				free(textureImage[0]->data);
			}
			free(textureImage[0]);
		}
	}
	sprintf_s(fileName, "Data/ConsumbleItem/Shield/Sacred Shield.bmp");
	if (textureImage[0] = loadBMP(fileName))
	{
		glGenTextures(1, &shieldTexture);
		glBindTexture(GL_TEXTURE_2D, shieldTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[0]->sizeX, textureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[0]->data);
		if (textureImage[0])
		{
			if (textureImage[0]->data)
			{
				free(textureImage[0]->data);
			}
			free(textureImage[0]);
		}
	}

	return status;
}

void Player::move(bool isUp)
{
	if(isUp)
		positionMoveTo = new Vector2(positionInMap->x - direction->x, positionInMap->y - direction->y);
	else
		positionMoveTo = new Vector2(positionInMap->x + direction->x, positionInMap->y + direction->y);
	status = PlayerStatus::moving;
}

void Player::spin(bool isLeft)
{
	if (isLeft)
		spinYTo = spinY + 90;
	else
		spinYTo = spinY - 90;
	status = PlayerStatus::spining;
}

void Player::display()
{
	if (status == PlayerStatus::moving)
	{
		if (fabsf(positionInMap->x - positionMoveTo->x) < moveSpeed/2 && fabsf(positionInMap->y - positionMoveTo->y) < moveSpeed/2)
			status = PlayerStatus::idle;
		else
		{
			if(direction->x == 0)
				position->x += (positionInMap->y - positionMoveTo->y < 0 ? 1 : -1) * lx * moveSpeed;
			else
				position->z += (positionInMap->x - positionMoveTo->x < 0 ? 1 : -1) * lz * moveSpeed;
			if(direction->y == 0)
				positionInMap->x += (positionInMap->x - positionMoveTo->x < 0 ? 1 : -1) * moveSpeed;
			else
				positionInMap->y += (positionInMap->y - positionMoveTo->y < 0 ? 1 : -1) * moveSpeed;
		}
	}
	else if (status == PlayerStatus::spining)
	{
		if (fabsf(spinY-spinYTo) < spinSpeed/2 || (int)fabsf(spinY - spinYTo)%360 < spinSpeed/2)
		{
			if ((int)spinY % 360 == 0)
				direction = new Vector2(1, 0); // 前
			else if ((int)spinY % 360 == 90 || (int)spinY%360 == -270)
				direction = new Vector2(0, 1); // 左
			else if ((int)spinY % 360 == 180 || (int)spinY % 360 == -180)
				direction = new Vector2(-1, 0); // 后
			else if ((int)spinY % 360 == 270 || (int)spinY % 360 == -90)
				direction = new Vector2(0, -1); // 右
			status = PlayerStatus::idle;
		}
		else
			spinY += (spinY - spinYTo) < 0 ? spinSpeed : -spinSpeed;
	}
	else if (status == PlayerStatus::battling)
	{
		counter++;
		if (counter == 15)
		{
			AudioManager::playSound("Data/Audio/battle.wav");
			if (index == 0)
			{
				int damage = attack - monster->getDefence();
				if (damage < 0)
					damage = 0;
				monster->receiveDamage(damage);
				if (monster->getHealth() <= 0)
				{
					this->money += monster->getMoney();
					finishBattle();
					monster->destroyThis();
				}
			}
			else
			{
				int damage = monster->getAttack() - defence;
				if (damage < 0)
					damage = 0;
				health -= damage;
				if (health < 0)
					health = 0;
			}
			index++;
			counter = 0;
		}
		if (index == 2)
			index = 0;
	}
}

void Player::draw2D(int width, int height)
{
	if (status == PlayerStatus::moving)
	{
		counter++;
		if (counter == 4)
		{
			index++;
			counter = 0;
		}
		if (index >= 4)
			index = 0;
	}
	else if(status == PlayerStatus::idle || status == PlayerStatus::spining)
		index = 0;
	glEnable(GL_TEXTURE_2D); // 开启2D纹理
	if (direction->x == 1)
		glBindTexture(GL_TEXTURE_2D, up[index]);		// 选择纹理
	else if (direction->x == -1)
		glBindTexture(GL_TEXTURE_2D, down[index]);		// 选择纹理
	else if (direction->y == 1)
		glBindTexture(GL_TEXTURE_2D, left[index]);		// 选择纹理
	else if (direction->y == -1)
		glBindTexture(GL_TEXTURE_2D, right[index]);		// 选择纹理
	if (status == PlayerStatus::battling && index == 0)
		glBindTexture(GL_TEXTURE_2D, battleTexture[0]);
	if(status == PlayerStatus::animating && this->floor == 3)
		glBindTexture(GL_TEXTURE_2D, battleTexture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glEnd();
}

void Player::upStairs(Vector2* position, Vector2* direction)
{
	floor++;
	if (floor > maxFloor)
		maxFloor = floor;
	this->direction = direction;
	if (direction->x == 1)
		spinY = 0; // 前
	else if (direction->y == 1)
		spinY = 90; // 左
	else if (direction->x == -1)
		spinY = 180; // 后
	else if (direction->y == -1)
		spinY = 270; // 右
	this->positionInMap->x = position->x;
	this->positionInMap->y = position->y;
	this->position = new Vector3(positionInMap->y * lx, ly / 2, positionInMap->x * lz); // 在3D世界中的位置可以按照2DMap中的位置计算
}

void Player::downStairs(Vector2* position, Vector2* direction)
{
	floor--;
	this->direction = direction;
	if (direction->x == 1)
		spinY = 0; // 前
	else if (direction->y == 1)
		spinY = 90;
	else if (direction->x == -1)
		spinY = 180; // 后
	else if (direction->y == -1)
		spinY = 270; // 右
	this->positionInMap->x = position->x;
	this->positionInMap->y = position->y;
	this->position = new Vector3(positionInMap->y * lx, ly / 2, positionInMap->x * lz); // 在3D世界中的位置可以按照2DMap中的位置计算
}

void Player::reciveItems(ConsumbleItem* consumbleItem)
{
	if (consumbleItem->getTag() == Tag::sword)
	{
		swordTexture = ((Sword*)consumbleItem)->getTexture();
		sprintf_s(swordName, ((Sword*)consumbleItem)->getUIName());
	}
	else if (consumbleItem->getTag() == Tag::shield)
	{
		shieldTexture = ((Shield*)consumbleItem)->getTexture();
		sprintf_s(shieldName, ((Shield*)consumbleItem)->getUIName());
	}

	// 将消耗物品的属性加到人物身上
	this->health += consumbleItem->getHealth();
	this->attack += consumbleItem->getAttack();
	this->defence += consumbleItem->getDefence();
	this->yellowKeyNumber += consumbleItem->getYellowKeyNumber();
	this->blueKeyNumber += consumbleItem->getBlueKeyNumber();
	this->redKeyNumber += consumbleItem->getRedKeyNumber();
}

void Player::reciveUseItems(UseItem* useItem)
{
	this->useItems[useItem->getIndex()]->enableItem();
}

void Player::SetDirection(Vector2* direction)
{
	this->direction = direction;
	if (direction->x == 1)
		spinY = 0; // 前
	else if (direction->y == 1)
		spinY = 90;
	else if (direction->x == -1)
		spinY = 180; // 后
	else if (direction->y == -1)
		spinY = 270; // 右
}

void Player::openDoor(int tag)
{
	if (tag == 0)
		yellowKeyNumber--;
	else if (tag == 1)
		blueKeyNumber--;
	else if (tag == 2)
		redKeyNumber--;
}

void Player::battle(Monster* monster)
{
	status = PlayerStatus::battling;
	this->monster = monster;
	this->index = 0;
}

void Player::talk(NPC* npc)
{
	this->status = PlayerStatus::talking;
	this->npc = npc;
}

void Player::talk(Boss* boss)
{
	this->status = PlayerStatus::talking;
	this->npc = boss;
}

void Player::action()
{
	if (strcmp(npc->getName(), "Old Man") == 0)
	{
		if(((OldMan*)npc)->getIndexOfUseItems() > -1)
		this->useItems[((OldMan*)npc)->getIndexOfUseItems()]->enableItem();
	}
	else if (strcmp(npc->getName(), "Merchant") == 0)
	{
		this->money -= ((Merchant*)npc)->getCost();
		this->yellowKeyNumber += ((Merchant*)npc)->getYellowKeyNumber();
		this->blueKeyNumber += ((Merchant*)npc)->getBlueKeyNumber();
		this->redKeyNumber += ((Merchant*)npc)->getRedKeyNumber();
	}
	else if (strcmp(npc->getName(), "Altar") == 0)
	{
		this->money -= ((Altar*)npc)->getCost();
		unsigned short i = ((Altar*)npc)->getIndexOfChoose();
		switch (i)
		{
		case 0:
			this->health += ((Altar*)npc)->getHealth();
			break;
		case 1:
			this->attack += ((Altar*)npc)->getAttack();
			break;
		case 2:
			this->defence += ((Altar*)npc)->getDefence();
			break;
		}
	}
	else if (strcmp(npc->getName(), "Thief") == 0)
	{

	}
}

Player::Player(Vector2* positionInMap): Creature(positionInMap)
{
	yellowKeyNumber = 0;
	blueKeyNumber = 0;
	redKeyNumber = 0;

	health = 1000;
	attack = 100;
	defence = 100;
	money = 0;
	
	moveSpeed = 0.05f;
	positionMoveTo = positionInMap;

	sprintf_s(this->swordName, "Sacred");
	swordTexture = 0;
	sprintf_s(this->shieldName, "Sacred");
	shieldTexture = 0;

	spinY = 0;
	spinSpeed = 2.5f;
	direction = new Vector2(1, 0);
	floor = 1;

	monster = NULL;

	for (int i = 0; i < 15; i++)
	{
		switch (i)
		{
		case 0:
			useItems[i] = new TheOrbOfTheHero(new Vector2(-1, -1));
			useItems[i]->init();
			break;
		case 1:
			useItems[i] = new TheOrbOfWisdom(new Vector2(-1, -1));
			useItems[i]->init();
			break;
		case 2:
			useItems[i] = new TheOrbOfFlying(new Vector2(-1, -1));
			useItems[i]->init();
			break;
		default:
			break;
		}
	}
}

void Player::load()
{
	Json::Reader reader;
	Json::Value playerValue;
	char fileName[100];
	sprintf_s(fileName, "Data/Save/Player.file");

	std::ifstream is(fileName, std::ios::binary);
	if (reader.parse(is, playerValue))
	{
		this->health = playerValue["health"].asUInt();
		this->attack = playerValue["attack"].asUInt();
		this->defence = playerValue["defence"].asUInt();
		this->money = playerValue["money"].asUInt();
		this->yellowKeyNumber = playerValue["yellowKeyNumber"].asUInt();
		this->blueKeyNumber = playerValue["blueKeyNumber"].asUInt();
		this->redKeyNumber = playerValue["redKeyNumber"].asUInt();
		this->positionInMap->x = (float)playerValue["PositionInMap"]["x"].asDouble();
		this->positionInMap->y = (float)playerValue["PositionInMap"]["y"].asDouble();
		this->position->x = positionInMap->y * lx;
		this->position->z = positionInMap->x * lz;
		this->swordTexture = playerValue["Sword"]["Texture"].asInt();
		sprintf_s(swordName, playerValue["Sword"]["Name"].asCString());
		this->shieldTexture = playerValue["Shield"]["Texture"].asInt();
		sprintf_s(shieldName, playerValue["Shield"]["Name"].asCString());
		this->spinY = (float)playerValue["spinY"].asDouble();
		this->floor = playerValue["floor"].asUInt();
		this->direction->x = (float)playerValue["direction"]["x"].asDouble();
		this->direction->y = (float)playerValue["direction"]["y"].asDouble();
	}
}

void Player::save()
{
	Json::Value playerValue;
	playerValue["health"] = this->health;
	playerValue["attack"] = this->attack;
	playerValue["defence"] = this->defence;
	playerValue["money"] = this->money;
	playerValue["yellowKeyNumber"] = this->yellowKeyNumber;
	playerValue["blueKeyNumber"] = this->blueKeyNumber;
	playerValue["redKeyNumber"] = this->redKeyNumber;
	playerValue["PositionInMap"]["x"] = this->positionInMap->x;
	playerValue["PositionInMap"]["y"] = this->positionInMap->y;
	playerValue["Sword"]["Texture"] = this->swordTexture;
	playerValue["Sword"]["Name"] = swordName;
	playerValue["Shield"]["Texture"] = this->shieldTexture;
	playerValue["Shield"]["Name"] = shieldName;
	playerValue["spinY"] = this->spinY;
	playerValue["floor"] = this->floor;
	playerValue["direction"]["x"] = this->direction->x;
	playerValue["direction"]["y"] = this->direction->y;

	Json::StyledWriter writer;

	std::ofstream os;
	char fileName[100];
	sprintf_s(fileName, "Data/Save/Player.file");
	os.open(fileName);
	os << writer.write(playerValue);
}
