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
}

void Player::draw2D(int width, int height)
{
	if (status == PlayerStatus::moving)
	{
		counter++;
		if (counter == 2)
		{
			index++;
			counter = 0;
		}
		if (index >= 4)
			index = 0;
	}
	else
		index = 0;
	glEnable(GL_TEXTURE_2D); // 开启2D纹理
	if(direction->x == 1)
		glBindTexture(GL_TEXTURE_2D, up[index]);		// 选择纹理
	else if (direction->x == -1)
		glBindTexture(GL_TEXTURE_2D, down[index]);		// 选择纹理
	else if (direction->y == 1)
		glBindTexture(GL_TEXTURE_2D, left[index]);		// 选择纹理
	else if (direction->y == -1)
		glBindTexture(GL_TEXTURE_2D, right[index]);		// 选择纹理
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
		swordName = ((Sword*)consumbleItem)->getUIName();
	}
	else if (consumbleItem->getTag() == Tag::shield)
	{
		shieldTexture = ((Shield*)consumbleItem)->getTexture();
		shieldName = ((Shield*)consumbleItem)->getUIName();
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

Player::Player(Vector2* positionInMap): Creature(positionInMap)
{
	yellowKeyNumber = 5;
	blueKeyNumber = 5;
	redKeyNumber = 5;
	
	moveSpeed = 0.1f;
	positionMoveTo = positionInMap;

	swordTexture = 0;
	swordName = "";
	shieldTexture = 0;
	shieldName = "";

	spinY = 0;
	spinSpeed = 5.0f;
	useItems = new std::vector<UseItem*>();
	direction = new Vector2(1, 0);
	floor = 1;
}
