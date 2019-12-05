#include "Monster.h"

void Monster::spin()
{

}

bool Monster::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[2];

	memset(textureImage, 0, sizeof(void*) * 2);

	char fileName[20];
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(fileName, "Data/Monster/%s/%s_%d.bmp", this->name, this->name,i);

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
}