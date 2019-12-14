#include "UIManager.h"

AUX_RGBImageRec* UIManager::loadBMP(char* fileName)
{
	FILE* file = NULL;
	if (!fileName)
		return NULL;

	fopen_s(&file, fileName, "r");
	if (file)
	{
		fclose(file);
		return auxDIBImageLoad(fileName);
	}

	return NULL;
}

void UIManager::BuildFont()
{
	float cx;							// 存储纹理x,y坐标的临时变量
	float cy;

	base = glGenLists(256);				// 存储256个字符
	glBindTexture(GL_TEXTURE_2D, font[0]);			// 选择字体的纹理
	for (int i = 0; i < 256; i++)					// 将256个字符都覆盖上纹理
	{
		cx = float(i % 16) / 16.0f;					// 16个字符一行，根据纹理选择字体模样（可以看一下Data/Font.bmp）
		cy = float(i / 16) / 16.0f;

		glNewList(base + i, GL_COMPILE);
		glBegin(GL_QUADS);								// 用一个正方形将纹理覆盖到字体上
		glTexCoord2f(cx, 1 - cy - 0.0625f);				// 纹理坐标 (左下)
		glVertex2i(0, 16);								// 正方形的点坐标 (左下)
		glTexCoord2f(cx + 0.0625f, 1 - cy - 0.0625f);	// 纹理坐标 (右下)
		glVertex2i(16, 16);								// 正方形的点坐标 (右下)
		glTexCoord2f(cx + 0.0625f, 1 - cy);				// 纹理坐标 (右上)
		glVertex2i(16, 0);								// 正方形的点坐标 (右上)
		glTexCoord2f(cx, 1 - cy);						// 纹理坐标 (左上)
		glVertex2i(0, 0);								// 正方形的点坐标 (左上)
		glEnd();
		glTranslated(10, 0, 0);							// 移动字符
		glEndList();
	}
}

void UIManager::glPrint(int x, int y, char* string, float scale)
{
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, font[0]);			// 选择字体纹理
	glTranslated(x, y, 0);								// 移动文本
	glScalef(scale, scale, 1);
	glListBase(base - 32);								// 创建显示列表
	glCallLists(strlen(string), GL_BYTE, string);		// 将文本投影到屏幕上
	glLoadIdentity();
	glDisable(GL_BLEND);
}

bool UIManager::loadTexture()
{
	bool status = false;

	AUX_RGBImageRec* textureImage[1];

	memset(textureImage, 0, sizeof(void*) * 1);

	char fileName[100];
	sprintf_s(fileName, "Data/UI/Left.bmp");

	if (textureImage[0] = loadBMP(fileName))
	{
		status = true;
		glGenTextures(1, &left[0]);
		glBindTexture(GL_TEXTURE_2D, left[0]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
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

	sprintf_s(fileName, "Data/UI/Right.bmp");

	if (textureImage[0] = loadBMP(fileName))
	{
		status = true;
		glGenTextures(1, &right[0]);
		glBindTexture(GL_TEXTURE_2D, right[0]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
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

	sprintf_s(fileName, "Data/UI/Bottom.bmp");

	if (textureImage[0] = loadBMP(fileName))
	{
		status = true;
		glGenTextures(1, &bottom[0]);
		glBindTexture(GL_TEXTURE_2D, bottom[0]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
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

	sprintf_s(fileName, "Data/UI/Font.bmp");

	if (textureImage[0] = loadBMP(fileName))
	{
		status = true;
		glGenTextures(1, &font[0]);
		glBindTexture(GL_TEXTURE_2D, font[0]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
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

bool UIManager::init()
{
	bool status = false;
	status = loadTexture();
	BuildFont();
	return status;
}

void UIManager::draw()
{
	glMatrixMode(GL_PROJECTION);						// 选择透视矩阵
	glLoadIdentity();									// 重设透视矩阵

	glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);   // 设置平行投影

	glMatrixMode(GL_MODELVIEW);							// 选择模型矩阵
	glLoadIdentity();									// 重新载入模型矩阵

	glEnable(GL_TEXTURE_2D); // 开启2D纹理
	glBindTexture(GL_TEXTURE_2D, left[0]);		// 选择纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(0, height * 20 / 21);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width * 3 / 16, height * 20 / 21);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width * 3 / 16, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
	glEnd();

	glEnable(GL_TEXTURE_2D); // 开启2D纹理
	glBindTexture(GL_TEXTURE_2D, right[0]);		// 选择纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(width * 13 / 16, height * 20 / 21);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width, height * 20 / 21);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(width * 13 / 16, 0);
	glEnd();

	glEnable(GL_TEXTURE_2D); // 开启2D纹理
	glBindTexture(GL_TEXTURE_2D, bottom[0]);		// 选择纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(0, height);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width, height);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width, height * 20 / 21);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(0, height * 20 / 21);
	glEnd();

	char string[100];
	// 显示层数
	sprintf_s(string, "Tower %d", 15);
	glPrint((int)(((float)40/1600)*width), (int)(((float)150/1200)*height), string, ((float)240 / (float)(strlen(string) * 11))/1600 * width);
	// 显示属性
	sprintf_s(string, "%d", player->getHealth());
	glPrint((int)((260 - strlen(string) * 32) / (float)1600 * width), (int)(((float)230 / 1200) * height), string, (float)3 / 1600 * width);
	sprintf_s(string, "%d", player->getAttack());
	glPrint((int)((260 - strlen(string) * 32) / (float)1600 * width), (int)(((float)298 / 1200) * height), string, (float)3 / 1600 * width);
	sprintf_s(string, "%d", player->getDefence());
	glPrint((int)((260 - strlen(string) * 32) / (float)1600 * width), (int)(((float)366 / 1200) * height), string, (float)3 / 1600 * width);
	sprintf_s(string, "%d", player->getMoney());
	glPrint((int)((260 - strlen(string) * 32) / (float)1600 * width), (int)(((float)434 / 1200) * height), string, (float)3 / 1600 * width);

	glEnable(GL_BLEND);
	GLuint texture;
	// 画主动道具
	for (unsigned short i = 0; i < player->getUseItem()->size(); i++)
	{
		int index = (*(player->getUseItem()))[i]->getIndex();
		texture = (*(player->getUseItem()))[i]->getTexture();

	}
	// 画剑和盾
	if (player->getSword() != NULL)
	{
		sprintf_s(string, "%s", player->getSword()->getUIName());
		texture = player->getSword()->getTexture();
	}
	// 画钥匙
	int index = 0;
	for (int i = 0; i < player->getRedKeyNumber(); i++)
	{
		// 画红钥匙
		index++;
	}
	for (int i = 0; i < player->getBlueKeyNumber(); i++)
	{
		// 画蓝钥匙
		index++;
	}
	for (int i = 0; i < player->getYellowKeyNumber(); i++)
	{
		// 画黄钥匙
		index++;
	}

	// 画怪物属性
	if (monster != NULL)
	{
		texture = monster->getTexture();
		sprintf_s(string, "%s", monster->getName());
		sprintf_s(string, "%d", monster->getHealth());
		sprintf_s(string, "%d", monster->getAttack());
		sprintf_s(string, "%d", monster->getDefence());
	}
	else
	{
		sprintf_s(string, "The Name");
		glPrint((int)((float)1328/1600 * width), (int)((float)770/1200*height), string, (2.5f / 1600) * width);
		sprintf_s(string, "Life");
		glPrint((int)((float)1400 / 1600 * width), (int)((float)828 / 1200 * height), string, (2.5f / 1600) * width);
		sprintf_s(string, "Offense");
		glPrint((int)((float)1400 / 1600 * width), (int)((float)886 / 1200 * height), string, (2.5f / 1600) * width);
		sprintf_s(string, "Defense");
		glPrint((int)((float)1400 / 1600 * width), (int)((float)944 / 1200 * height), string, (2.5f / 1600) * width);
	}
	glMatrixMode(GL_PROJECTION);						// 选择透视矩阵
	glLoadIdentity();									// 重设透视矩阵

	gluPerspective(45.0f, 1, 0.1f, 1000.0f); //	设置回透视投影

	glMatrixMode(GL_MODELVIEW);							// 选择模型矩阵
	glLoadIdentity();									// 重新载入模型矩阵
}

void UIManager::loadMonster(Monster* monster)
{
	this->monster = monster;
}

UIManager::UIManager(int width, int height, Player* player)
{
	this->width = width;
	this->height = height;
	this->player = player;
	this->monster = NULL;
}

void UIManager::setWindow(int width, int height)
{
	this->width = width;
	this->height = height;
}
