#include "Wall.h"

bool Wall::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[1];

	memset(textureImage, 0, sizeof(void*) * 1);

	char fileName[100];
	sprintf_s(fileName, "Data/Obstacle/wall.bmp");

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

Wall::Wall(Vector2* positionInMap): Object(positionInMap)
{
	this->name = "Wall";
	this->tag = Tag::wall;
}

void Wall::destroy()
{
}

void Wall::appear()
{
}

void Wall::collide()
{
}

void Wall::draw2D()
{
}

void Wall::draw3D()
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	// ������
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2), -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2), -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2), (ly / 2), (lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2), (ly / 2), (lz / 2));
	// ������
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-(lx / 2), -(ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-(lx / 2), (ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f((lx / 2), (ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 0.0f); glVertex3f((lx / 2), -(ly / 2), -(lz / 2));
	// ������
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2), (ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2), (ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2), (ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2), (ly / 2), -(lz / 2));
	// ������
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-(lx / 2), -(ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f((lx / 2), -(ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 0.0f); glVertex3f((lx / 2), -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-(lx / 2), -(ly / 2), (lz / 2));
	// ���Ҳ���
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2), -(ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2), (ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f((lx / 2), (ly / 2), (lz / 2));
	glTexCoord2f(0.0f, 0.0f); glVertex3f((lx / 2), -(ly / 2), (lz / 2));
	// �������
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2), -(ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-(lx / 2), -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-(lx / 2), (ly / 2), (lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2), (ly / 2), -(lz / 2));

	glEnd();
	glPopMatrix();
}