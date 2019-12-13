#include "ConsumbleItem.h"

void ConsumbleItem::lookAt(Vector3* position)
{
	// ��������û����
	Vector3* direction = new Vector3(position->x - this->position->x, position->y - this->position->y, position->z - this->position->z);
	if (direction->x < 0)
		spinY = -acosf(direction->z / sqrtf(powf(direction->x, 2) + powf(direction->y, 2) + powf(direction->z, 2)));
	else
		spinY = acosf(direction->z / sqrtf(powf(direction->x, 2) + powf(direction->y, 2) + powf(direction->z, 2)));

}

bool ConsumbleItem::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[1];

	memset(textureImage, 0, sizeof(void*) * 1);

	char fileName[100];
	sprintf_s(fileName, "Data/ConsumbleItem/%s.bmp", this->name);

	if (textureImage[0] = loadBMP(fileName))
	{
		status = true;
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]); // ʹ��������������ӽ������ɸ���ɫ��ͨ����Ȩƽ���㷨�õ���Ҫ���Ƶ�������ɫ
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[0]->sizeX, textureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[0]->data);
	}

	if (textureImage[0])
	{
		if (textureImage[0]->data)
		{
			free(textureImage[0]->data);
		}
		free(textureImage[0]);
	}

	return status;
}

void ConsumbleItem::draw2D()
{
}

void ConsumbleItem::draw3D()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRotatef(spinY, 0, 1, 0); // ��Y����תһ��
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); // ��������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-lx / 2, -ly / 2, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(lx / 2, -ly / 2, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(lx / 2, ly / 2, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-lx / 2, ly / 2, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}

void ConsumbleItem::collide()
{
}

ConsumbleItem::ConsumbleItem(Vector2* positionInMap): Object(positionInMap)
{
}
