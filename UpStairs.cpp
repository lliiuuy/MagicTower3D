#include "UpStairs.h"

bool UpStairs::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[1];

	memset(textureImage, 0, sizeof(void*) * 1);

	char fileName[100];
	sprintf_s(fileName, "Data/Obstacle/UpStairs.bmp");

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

	sprintf_s(fileName, "Data/Obstacle/Stairs.bmp");

	if (textureImage[0] = loadBMP(fileName))
	{
		status = true;
		glGenTextures(1, &texture[1]);
		glBindTexture(GL_TEXTURE_2D, texture[1]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
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

UpStairs::UpStairs(Vector2* positionInMap): Obstacle(positionInMap)
{
	this->name = "UpStairs";
	this->tag = Tag::upStairs;
	this->spinY = 90;
}

void UpStairs::collide()
{

}

void UpStairs::draw3D()
{
	glPushMatrix();
	glTranslatef(position->x, position->y - ly / 2 - ly / 20, position->z);
	glRotatef(spinY, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	for (int i = 1; i <= 10; i++)
	{
		glBegin(GL_QUADS);
		// 画正面
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2), ly * i / 10 - (ly / 20), (lz * (12 - 2 * i) / 20));
		glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2), ly * i / 10 - (ly / 20), (lz * (12 - 2 * i) / 20));
		glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2), ly * i / 10 + (ly / 20), (lz * (12 - 2 * i) / 20));
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2), ly * i / 10 + (ly / 20), (lz * (12 - 2 * i) / 20));
		// 画背面
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-(lx / 2), ly * i / 10 - (ly / 20), -(lz / 2));
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-(lx / 2), ly * i / 10 + (ly / 20), -(lz / 2));
		glTexCoord2f(0.0f, 1.0f); glVertex3f((lx / 2), ly * i / 10 + (ly / 20), -(lz / 2));
		glTexCoord2f(0.0f, 0.0f); glVertex3f((lx / 2), ly * i / 10 - (ly / 20), -(lz / 2));
		// 画顶面
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2), ly * i / 10 + (ly / 20), -(lz / 2));
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2), ly * i / 10 + (ly / 20), (lz * (12 - 2 * i) / 20));
		glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2), ly * i / 10 + (ly / 20), (lz * (12 - 2 * i) / 20));
		glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2), ly * i / 10 + (ly / 20), -(lz / 2));
		// 画底面
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-(lx / 2), ly * i / 10 - (ly / 20), -(lz / 2));
		glTexCoord2f(0.0f, 1.0f); glVertex3f((lx / 2), ly * i / 10 - (ly / 20), -(lz / 2));
		glTexCoord2f(0.0f, 0.0f); glVertex3f((lx / 2), ly * i / 10 - (ly / 20), (lz * (12 - 2 * i) / 20));
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-(lx / 2), ly * i / 10 - (ly / 20), (lz * (12 - 2 * i) / 20));
		// 画右侧面
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f((lx / 2), ly * i / 10 - (ly / 20), -(lz / 2));
		glTexCoord2f(1.0f, 1.0f); glVertex3f((lx / 2), ly * i / 10 + (ly / 20), -(lz / 2));
		glTexCoord2f(0.0f, 1.0f); glVertex3f((lx / 2), ly * i / 10 + (ly / 20), (lz * (12 - 2 * i) / 20));
		glTexCoord2f(0.0f, 0.0f); glVertex3f((lx / 2), ly * i / 10 - (ly / 20), (lz * (12 - 2 * i) / 20));
		// 画左侧面
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-(lx / 2), ly * i / 10 - (ly / 20), -(lz / 2));
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-(lx / 2), ly * i / 10 - (ly / 20), (lz * (12 - 2 * i) / 20));
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-(lx / 2), ly * i / 10 + (ly / 20), (lz * (12 - 2 * i) / 20));
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-(lx / 2), ly * i / 10 + (ly / 20), -(lz / 2));

		glEnd();
	}
	glPopMatrix();
}

void UpStairs::lookAt(Vector3* position)
{
	if (position->x == 1)
		spinY = 0;
	else if (position->x == -1)
		spinY = 180;
	else if (position->y == 1)
		spinY = 90;
	else if (position->y == -1)
		spinY = -90;
}
