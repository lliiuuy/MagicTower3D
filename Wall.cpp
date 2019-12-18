#include "Wall.h"

bool Wall::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[4];

	memset(textureImage, 0, sizeof(void*) * 4);

	char fileName[100];
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(fileName, "Data/Obstacle/Wall/Wall_%d.bmp", i + 1);

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

Wall::Wall(Vector2* positionInMap): Obstacle(positionInMap)
{
	this->name = "Wall";
	this->tag = Tag::wall;
	this->brokenWall = false;
	this->appearWall = false;
	this->index = 0;
}

void Wall::display(Vector3* position)
{
	if (action)
	{
		if (brokenWall)
		{
			counter++;
			this->position->y -= ly / 40;
			if(counter == 10)
			{
				index++;
				if (index == 4)
					destroy = true;
				counter = 0;
			}
		}
		else if (appearWall)
		{
			counter++;
			this->position->y += ly / 40;
			if (counter == 10)
			{
				index--;
				if (index == -1)
				{
					appearWall = false;
					action = false;
				}
				counter = 0;
			}
		}
	}
}

void Wall::collide()
{
	if ((brokenWall || appearWall) && !action)
	{
		AudioManager::playSound("Data/Audio/open.wav");
		action = true;
		counter = 0;
	}
}

void Wall::draw2D(int width, int height)
{
	if (action)
		glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D); // 开启2D纹理
	glBindTexture(GL_TEXTURE_2D, texture[index]);		// 选择纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 + 16) / 1200);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 + 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (930 + positionInMap->y * 32 - 16) / 1600, height * (784 + positionInMap->x * 32 - 16) / 1200);
	glEnd();
	if (action)
		glDisable(GL_BLEND);
}
