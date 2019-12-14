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
	 // 门有两片
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRotatef(spinY, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// 画左侧的门
	glBegin(GL_QUADS);
	// 画正面
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2) - move, -(ly / 2), (lz / 2));
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0 - move, -(ly / 2), (lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0 - move, (ly / 2), (lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2) - move, (ly / 2), (lz / 2));
	// 画背面
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2) - move, -(ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2) - move, (ly / 2), -(lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0 - move, (ly / 2), -(lz / 2));
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0 - move, -(ly / 2), -(lz / 2));
	// 画右侧面
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0 - move, -(ly / 2), -(lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0 - move, (ly / 2), -(lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0 - move, (ly / 2), (lz / 2));
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0 - move, -(ly / 2), (lz / 2));
	// 画左侧面
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2) - move, -(ly / 2), -(lz / 2));
	glTexCoord2f(0.5f, 0.0f); glVertex3f(-(lx / 2) - move, -(ly / 2), (lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(-(lx / 2) - move, (ly / 2), (lz / 2));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2) - move, (ly / 2), -(lz / 2));

	glEnd();

	// 画右侧面
	glBegin(GL_QUADS);
	// 画正面
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0 + move, -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2) + move, -(ly / 2), (lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2) + move, (ly / 2), (lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0 + move, (ly / 2), (lz / 2));
	// 画背面
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0 + move, -(ly / 2), -(lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0 + move, (ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2) + move, (ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2) + move, -(ly / 2), -(lz / 2));
	// 画右侧面
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2) + move, -(ly / 2), -(lz / 2));
	glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2) + move, (ly / 2), -(lz / 2));
	glTexCoord2f(0.5f, 1.0f); glVertex3f((lx / 2) + move, (ly / 2), (lz / 2));
	glTexCoord2f(0.5f, 0.0f); glVertex3f((lx / 2) + move, -(ly / 2), (lz / 2));
	// 画左侧面
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
