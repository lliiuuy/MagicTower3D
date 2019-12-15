#include "NPC.h"

bool NPC::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[2];

	memset(textureImage, 0, sizeof(void*) * 2);

	char fileName[100];
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(fileName, "Data/NPC/%s/%s_%d.bmp", this->name, this->name, i + 1);

		if (textureImage[i] = loadBMP(fileName))
		{
			status = true;
			glGenTextures(1, &texture[i]);
			glBindTexture(GL_TEXTURE_2D, texture[i]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[i]->sizeX, textureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[i]->data);
		}

		if (textureImage[i])
		{
			if (textureImage[i]->data)
			{
				free(textureImage[i]->data);
			}
			free(textureImage[i]);
		}
	}

	return status;
}

void NPC::collide()
{
}

void NPC::draw3D()
{
	counter++;
	if (counter >= 5)
	{
		index = index == 1 ? 0 : 1;
		counter = 0;
	}
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRotatef(spinY, 0, 1, 0); // 绕Y轴旋转一下
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	glBindTexture(GL_TEXTURE_2D, texture[index]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); // 朝向正面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-lx / 2, -ly / 2, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(lx / 2, -ly / 2, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(lx / 2, ly / 2, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-lx / 2, ly / 2, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}

void NPC::draw2D(int width, int height)
{
	glEnable(GL_TEXTURE_2D); // 开启2D纹理
	glBindTexture(GL_TEXTURE_2D, texture[index]);		// 选择纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glEnd();
}

void NPC::lookAt(Vector3* position)
{
	// 经过测试没问题
	Vector3* direction = new Vector3(position->x - this->position->x, position->y - this->position->y, position->z - this->position->z);
	if (direction->x < 0)
		spinY = -acosf(direction->z / sqrtf(powf(direction->x, 2) + powf(direction->z, 2))) * 180 / (float)M_PI;
	else
		spinY = acosf(direction->z / sqrtf(powf(direction->x, 2) + powf(direction->z, 2))) * 180 / (float)M_PI;
}

NPC::NPC(Vector2* positionInMap): Object(positionInMap)
{
	this->tag = Tag::NPC;
	this->indexOfMessage = 0;
	this->index = 0;
}
