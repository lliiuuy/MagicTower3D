#include "Floor.h"

bool Floor::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[1];

	memset(textureImage, 0, sizeof(void*) * 1);

	char fileName[100];
	sprintf_s(fileName, "Data/Obstacle/Floor.bmp");

	if (textureImage[0] = loadBMP(fileName))
	{
		status = true;
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
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

Floor::Floor(Vector2* positionInMap, bool isFloor): Obstacle(positionInMap)
{
	this->tag = Tag::floor;
	this->name = "Floor";
	if (isFloor)
		this->position->y = 0;
	else
		this->position->y = ly;
}

void Floor::draw3D()
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	if (this->position->y == 0)
		glNormal3f(0.0f, 1.0f, 0.0f);
	else
		glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2), 0, -(lz / 2));
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2), 0, (lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2), 0, (lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2), 0, -(lz / 2));
	glEnd();
	glPopMatrix();
}
