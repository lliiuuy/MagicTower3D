#include "Player.h"

bool Player::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[4];

	memset(textureImage, 0, sizeof(void*) * 4);

	char fileName[100];
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
			positionInMap->x += (positionInMap->x - positionMoveTo->x < 0 ? 1 : -1) * moveSpeed;
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
}

void Player::draw2D()
{
}

void Player::reciveItems(ConsumbleItem* consumbleItem)
{
	if (consumbleItem->getTag() == Tag::sword)
		this->sword = (Sword*)consumbleItem;
	else if (consumbleItem->getTag() == Tag::shield)
		this->shield = (Shield*)consumbleItem;
	// 将消耗物品的属性加到人物身上
	this->health += consumbleItem->getHealth();
	this->attack += consumbleItem->getAttack();
	this->defence += consumbleItem->getDefence();
	this->yellowKeyNumber += consumbleItem->getYellowKeyNumber();
	this->blueKeyNumber += consumbleItem->getBlueKeyNumber();
	this->redKeyNumber += consumbleItem->getRedKeyNumber();

	// 更新UI界面
	// UIManager.update();
}

void Player::reciveUseItems(UseItem* useItem)
{
	// 将UI界面上的UseItem图标激活
	// unsigned short index = useItem->get
	// UIManager.enableUseItem(index)
	// UIManager.update();
	// 将物体插入指定位置
	// useItems->insert(index, useItem);
}

Player::Player(Vector2* positionInMap): Creature(positionInMap)
{
	// 测试
	yellowKeyNumber = 6;
	blueKeyNumber = 6;
	redKeyNumber = 6;
	
	moveSpeed = 0.1f;
	positionMoveTo = positionInMap;
	// 测试
	shield = new IronShield(new Vector2(-1, -1));
	shield->init();
	sword = new IronSword(new Vector2(-1, -1));
	sword->init();
	
	spinY = 0;
	spinSpeed = 5.0f;
	useItems = new std::vector<UseItem*>();
	direction = new Vector2(1, 0);
	floor = 1;
}
