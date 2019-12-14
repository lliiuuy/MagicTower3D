#include "Door.h"

bool Door::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[1];

	memset(textureImage, 0, sizeof(void*) * 1);

	char fileName[100];
	sprintf_s(fileName, "Data/Obstacle/Door/%s.bmp", this->name);

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

void Door::open()
{
	move++;
	if (move >= lx / 2)
		delete this;
}

void Door::collide()
{
	open();
}

void Door::draw3D()
{
	 // ������Ƭ
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRotatef(spinY, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// ��������
	glBegin(GL_QUADS);
	// ������
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2) - move, -(ly / 2), (lz / 2));
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0 - move, -(ly / 2), (lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0 - move, (ly / 2), (lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2) - move, (ly / 2), (lz / 2));
	// ������
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2) - move, -(ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2) - move, (ly / 2), -(lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0 - move, (ly / 2), -(lz / 2));
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0 - move, -(ly / 2), -(lz / 2));
	// ���Ҳ���
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0 - move, -(ly / 2), -(lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0 - move, (ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0 - move, (ly / 2), (lz / 2));
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0 - move, -(ly / 2), (lz / 2));
	// �������
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2) - move, -(ly / 2), -(lz / 2));
	glTexCoord2f(0.5f, 0.0f); glVertex3f(-(lx / 2) - move, -(ly / 2), (lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(-(lx / 2) - move, (ly / 2), (lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2) - move, (ly / 2), -(lz / 2));

	glEnd();

	// ���Ҳ���
	glBegin(GL_QUADS);
	// ������
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0 + move, -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2) + move, -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2) + move, (ly / 2), (lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0 + move, (ly / 2), (lz / 2));
	// ������
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0 + move, -(ly / 2), -(lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0 + move, (ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2) + move, (ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2) + move, -(ly / 2), -(lz / 2));
	// ���Ҳ���
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2) + move, -(ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2) + move, (ly / 2), -(lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f((lx / 2) + move, (ly / 2), (lz / 2));
	glTexCoord2f(0.5f, 0.0f); glVertex3f((lx / 2) + move, -(ly / 2), (lz / 2));
	// �������
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0 + move, -(ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0 + move, -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0 + move, (ly / 2), (lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0 + move, (ly / 2), -(lz / 2));

	glEnd();

	glPopMatrix();
}

void Door::lookAt(Vector3* position)
{
	spinY = 90;
}

Door::Door(Vector2* positionInMap): Obstacle(positionInMap)
{
	this->tag = Tag::door;
	this->move = 0;
	this->spinY = 0;
}
