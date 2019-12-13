#include "Monster.h"

void Monster::lookAt(Vector3* position)
{
	// ��������û����
	Vector3* direction = new Vector3(position->x - this->position->x, position->y - this->position->y, position->z - this->position->z);
	if(direction->x < 0)
		spinY = -acosf(direction->z / sqrtf(powf(direction->x, 2) + powf(direction->y, 2) + powf(direction->z, 2)));
	else
		spinY = acosf(direction->z / sqrtf(powf(direction->x, 2) + powf(direction->y, 2) + powf(direction->z, 2)));
}

bool Monster::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[2];

	memset(textureImage, 0, sizeof(void*) * 2);

	char fileName[100];
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(fileName, "Data/Creature/Monster/%s/%s_%d.bmp", this->name, this->name, i+1);

		if (textureImage[i] = loadBMP(fileName))
		{
			status = true;
			glGenTextures(1, &texture[i]);
			glBindTexture(GL_TEXTURE_2D, texture[i]); // ʹ��������������ӽ������ɸ���ɫ��ͨ����Ȩƽ���㷨�õ���Ҫ���Ƶ�������ɫ
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

Monster::Monster(Vector2* positionInMap): Creature(positionInMap)
{
	this->tag = Tag::monster;
}

void Monster::collide()
{
}

void Monster::draw2D()
{
}

void Monster::draw3D()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRotatef(spinY, 0, 1, 0); // ��Y����תһ��
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); // ��������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-lx/2, -ly/2, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(lx/2, -ly/2, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(lx/2, ly/2, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-lx/2, ly/2, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}