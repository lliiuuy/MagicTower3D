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
	glBindTexture(GL_TEXTURE_2D, font[0]);			// 选择字体纹理
	glTranslated(x, y, 0);								// 移动文本
	glScalef(scale, scale, 1);
	glListBase(base - 32);								// 创建显示列表
	glCallLists(strlen(string), GL_BYTE, string);		// 将文本投影到屏幕上
	glLoadIdentity();
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

	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			sprintf_s(fileName, "Data/UI/Red Key.bmp");
			break;
		case 1:
			sprintf_s(fileName, "Data/UI/Blue Key.bmp");
			break;
		case 2:
			sprintf_s(fileName, "Data/UI/Yellow Key.bmp");
			break;
		default:
			break;
		}

		if (textureImage[0] = loadBMP(fileName))
		{
			status = true;
			glGenTextures(1, &key[i]);
			glBindTexture(GL_TEXTURE_2D, key[i]); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
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
	}

	sprintf_s(fileName, "Data/UI/UsingStairs.bmp");

	if (textureImage[0] = loadBMP(fileName))
	{
		status = true;
		glGenTextures(1, &usingStairs);
		glBindTexture(GL_TEXTURE_2D, usingStairs); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
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

	sprintf_s(fileName, "Data/UI/Dialog.bmp");

	if (textureImage[0] = loadBMP(fileName))
	{
		status = true;
		glGenTextures(1, &dialogTexture);
		glBindTexture(GL_TEXTURE_2D, dialogTexture); // 使用纹理中坐标最接近的若干个颜色，通过加权平均算法得到需要绘制的像素颜色
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

void UIManager::draw(Player* player)
{
	// 画左边的UI
	glEnable(GL_TEXTURE_2D); // 开启2D纹理
	glBindTexture(GL_TEXTURE_2D, left[0]);		// 选择纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(0, height * 20 / 21);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width * 3 / 16, height * 20 / 21);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width * 3 / 16, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
	glEnd();
	// 画右边的UI框
	glEnable(GL_TEXTURE_2D); // 开启2D纹理
	glBindTexture(GL_TEXTURE_2D, right[0]);		// 选择纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(width * 13 / 16, height * 20 / 21);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width, height * 20 / 21);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(width * 13 / 16, 0);
	glEnd();
	// 画底下的信息框
	glEnable(GL_TEXTURE_2D); // 开启2D纹理
	glBindTexture(GL_TEXTURE_2D, bottom[0]);		// 选择纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(0, height);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width, height);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width, height * 20 / 21);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(0, height * 20 / 21);
	glEnd();

	glEnable(GL_BLEND);
	// 显示message
	if (messaging)
	{
		float scale;
		if (strlen(message) * 18.0f > 1600)
			scale = 1600 / strlen(message) * 18.0f;
		else
			scale = 3;
		glPrint(width * 5 / 1600, height * ((1200 * 20 / 21) + 5) / 1200, this->message, scale / 1600 * width);
	}

	char string[100];
	// 显示层数
	sprintf_s(string, "Tower %d", player->getFloor());
	glPrint((int)(((float)38/1600)*width), (int)(((float)148/1200)*height), string, ((float)240 / (float)(strlen(string) * 11.5f))/1600 * width);
	// 显示属性
	sprintf_s(string, "%d", player->getHealth());
	glPrint((int)((260 - strlen(string) * 32) / (float)1600 * width), (int)(((float)230 / 1200) * height), string, (float)3 / 1600 * width);
	sprintf_s(string, "%d", player->getAttack());
	glPrint((int)((260 - strlen(string) * 32) / (float)1600 * width), (int)(((float)298 / 1200) * height), string, (float)3 / 1600 * width);
	sprintf_s(string, "%d", player->getDefence());
	glPrint((int)((260 - strlen(string) * 32) / (float)1600 * width), (int)(((float)366 / 1200) * height), string, (float)3 / 1600 * width);
	sprintf_s(string, "%d", player->getMoney());
	glPrint((int)((260 - strlen(string) * 32) / (float)1600 * width), (int)(((float)434 / 1200) * height), string, (float)3 / 1600 * width);

	GLuint texture;
	// 画主动道具
	for (unsigned short i = 0; i < 15; i++)
	{
		if (player->getUseItems()[i] != NULL)
		{
			if ((player->getUseItems()[i])->isEnable())
			{
				texture = (player->getUseItems()[i])->getTexture();
				glEnable(GL_TEXTURE_2D); // 开启2D纹理
				glBindTexture(GL_TEXTURE_2D, texture);		// 选择纹理
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (76 + 75 * (i % 3) - 36) / 1600, height * (596 + 88 * (i / 3) + 36) / 1200);
				glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (76 + 75 * (i % 3) + 36) / 1600, height * (596 + 88 * (i / 3) + 36) / 1200);
				glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (76 + 75 * (i % 3) + 36) / 1600, height * (596 + 88 * (i / 3) - 36) / 1200);
				glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (76 + 75 * (i % 3) - 36) / 1600, height * (596 + 88 * (i / 3) - 36) / 1200);
				glEnd();
			}
		}
	}
	// 画剑和盾
	if (player->getSwordTexture() != 0)
	{
		sprintf_s(string, "%s", player->getSwordName());
		glPrint(width * 1328 / 1600, height * 192 / 1200, string, width * 2.4f / 1600);

		texture = player->getSwordTexture();
		glEnable(GL_TEXTURE_2D); // 开启2D纹理
		glBindTexture(GL_TEXTURE_2D, texture);		// 选择纹理
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (1526 - 36) / 1600, height * 223 / 1200);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (1526 + 36) / 1600, height * 223 / 1200);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (1526 + 36) / 1600, height * 151 / 1200);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (1526 - 36) / 1600, height * 151 / 1200);
		glEnd();
	}
	if (player->getShieldTexture() != 0)
	{
		sprintf_s(string, "%s", player->getShieldName());
		glPrint(width * 1328 / 1600, height * 332 / 1200, string, width * 2.4f / 1600);

		texture = player->getShieldTexture();
		glEnable(GL_TEXTURE_2D); // 开启2D纹理
		glBindTexture(GL_TEXTURE_2D, texture);		// 选择纹理
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (1526 - 36) / 1600, height * 363 / 1200);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (1526 + 36) / 1600, height * 363 / 1200);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (1526 + 36) / 1600, height * 291 / 1200);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (1526 - 36) / 1600, height * 291 / 1200);
		glEnd();
	}
	// 画钥匙
	int index = 0;
	for (int i = 0; i < player->getRedKeyNumber(); i++)
	{
		// 画红钥匙
		texture = key[0];
		if (index < 24)
		{
			glEnable(GL_TEXTURE_2D); // 开启2D纹理
			glBindTexture(GL_TEXTURE_2D, texture);		// 选择纹理
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (1327 + (index % 6) * (double)234 / 6) / 1600, height * (409 + ((double)(index / 6) + 1) * (double)185 / 4) / 1200);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (1327 + ((double)(index % 6) + 1) * (double)234 / 6) / 1600, height * (409 + ((double)(index / 6) + 1) * (double)185 / 4) / 1200);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (1327 + ((double)(index % 6) + 1) * (double)234 / 6) / 1600, height * (409 + (index / 6) * (double)185 / 4) / 1200);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (1327 + (index%6) * (double)234/6) / 1600, height * (409 + (index/6) * (double)185/4) / 1200);
			glEnd();
		}
		index++;
	}
	for (int i = 0; i < player->getBlueKeyNumber(); i++)
	{
		// 画蓝钥匙
		texture = key[1];

		if (index < 24)
		{
			glEnable(GL_TEXTURE_2D); // 开启2D纹理
			glBindTexture(GL_TEXTURE_2D, texture);		// 选择纹理
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (1327 + (index % 6) * (double)234 / 6) / 1600, height * (409 + ((double)(index / 6) + 1) * (double)185 / 4) / 1200);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (1327 + ((double)(index % 6) + 1) * (double)234 / 6) / 1600, height * (409 + ((double)(index / 6) + 1) * (double)185 / 4) / 1200);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (1327 + ((double)(index % 6) + 1) * (double)234 / 6) / 1600, height * (409 + (index / 6) * (double)185 / 4) / 1200);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (1327 + (index % 6) * (double)234 / 6) / 1600, height * (409 + (index / 6) * (double)185 / 4) / 1200);
			glEnd();
		}
		index++;
	}
	for (int i = 0; i < player->getYellowKeyNumber(); i++)
	{
		// 画黄钥匙
		texture = key[2];
		if (index < 24)
		{
			glEnable(GL_TEXTURE_2D); // 开启2D纹理
			glBindTexture(GL_TEXTURE_2D, texture);		// 选择纹理
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (1327 + (index % 6) * (double)234 / 6) / 1600, height * (409 + ((double)(index / 6) + 1) * (double)185 / 4) / 1200);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (1327 + ((double)(index % 6) + 1) * (double)234 / 6) / 1600, height * (409 + ((double)(index / 6) + 1) * (double)185 / 4) / 1200);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (1327 + ((double)(index % 6) + 1) * (double)234 / 6) / 1600, height * (409 + (index / 6) * (double)185 / 4) / 1200);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (1327 + (index%6) * (double)234/6) / 1600, height * (409 + (index/6) * (double)185/4) / 1200);
			glEnd();
		}
		index++;
	}

	// 画怪物属性
	if (monster != NULL)
	{
		// 画怪物纹理
		texture = monster->getTexture();
		glEnable(GL_TEXTURE_2D); // 开启2D纹理
		glBindTexture(GL_TEXTURE_2D, texture);		// 选择纹理
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (1450 - 65) / 1600, height * 760 / 1200);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (1450 + 65) / 1600, height * 760 / 1200);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (1450 + 65) / 1600, height * 630 / 1200);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (1450 - 65) / 1600, height * 630 / 1200);
		glEnd();

		sprintf_s(string, "%s", monster->getName());
		if(strlen(string) > 10)
			glPrint((int)((float)1328 / 1600 * width), (int)((float)774 / 1200 * height), string, (width * ((float)240 / (strlen(string)* 11.2f))) / 1600);
		else
			glPrint((int)((float)1328 / 1600 * width), (int)((float)774 / 1200 * height), string, (2.2f / 1600) * width);
		sprintf_s(string, "%d", monster->getHealth());
		glPrint((int)((float)1400 / 1600 * width), (int)((float)832 / 1200 * height), string, (2.2f / 1600) * width);
		sprintf_s(string, "%d", monster->getAttack());
		glPrint((int)((float)1400 / 1600 * width), (int)((float)890 / 1200 * height), string, (2.2f / 1600) * width);
		sprintf_s(string, "%d", monster->getDefence());
		glPrint((int)((float)1400 / 1600 * width), (int)((float)948 / 1200 * height), string, (2.2f / 1600) * width);
	}
	else
	{
		sprintf_s(string, "The Name");
		glPrint((int)((float)1328/1600 * width), (int)((float)772/1200*height), string, (2.5f / 1600) * width);
		sprintf_s(string, "Life");
		glPrint((int)((float)1400 / 1600 * width), (int)((float)832 / 1200 * height), string, (2.2f / 1600) * width);
		sprintf_s(string, "Offense");
		glPrint((int)((float)1400 / 1600 * width), (int)((float)890 / 1200 * height), string, (2.2f / 1600) * width);
		sprintf_s(string, "Defense");
		glPrint((int)((float)1400 / 1600 * width), (int)((float)948 / 1200 * height), string, (2.2f / 1600) * width);
	}
	glDisable(GL_BLEND);

	// 对话框绘制
	if (dialogDrawing)
	{
		glEnable(GL_TEXTURE_2D); // 开启2D纹理
		glBindTexture(GL_TEXTURE_2D, dialogTexture);		// 选择纹理
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(width* 320 / 1600, height* 690 / 1200);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(width* 1280 / 1600, height* 690 / 1200);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(width* 1280 / 1600, height* 50 / 1200);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(width* 320 / 1600, height* 50 / 1200);
		glEnd();
		glEnable(GL_BLEND);
		char* word = NULL;
		char* nextWord = NULL;
		char words[1000];
		sprintf_s(words, sentence);
		word = strtok_s(words, "#", &nextWord);

		int i = 0;
		while (word != NULL)
		{
			if (word != NULL)
			{
				glPrint(width * 320 / 1600, height* (60 +40 * i)/ 1200, word, width * (float)2 / 1600);
				word = strtok_s(NULL, "#", &nextWord);
				i++;
			}
		}

		if (isChoose)
		{
			glPrint(width * 1170 / 1600, height* 600 / 1200, "Yes", width * (float)2 / 1600);
			glPrint(width * 1184 / 1600, height* 640 / 1200, "No", width * (float)2 / 1600);
		}
		glDisable(GL_BLEND);
	}

	// 对主动道具进行操作
	for (int i = 0; i < 15; i++)
	{
		if (player->getUseItems()[i] != NULL)
		{
			if (player->getUseItems()[i]->ifIsUsing())
			{
				switch (i)
				{
				case 0: // The orb of the hero
				{
					glBindTexture(GL_TEXTURE_2D, dialogTexture); // 选择纹理
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex2d(width * 3 / 16, height * 20 / 21);
					glTexCoord2f(1.0f, 0.0f); glVertex2d(width * 13 / 16, height * 20 / 21);
					glTexCoord2f(1.0f, 1.0f); glVertex2d(width * 13 / 16, 0);
					glTexCoord2f(0.0f, 1.0f); glVertex2d(width * 3 / 16, 0);
					glEnd();
					glEnable(GL_BLEND);
					for (int j = 0; j < (int)((TheOrbOfTheHero*)player->getUseItems()[i])->getSize(); j++)
					{
						glBindTexture(GL_TEXTURE_2D, ((TheOrbOfTheHero*)player->getUseItems()[i])->getTextureOfMonster(j)); // 先画纹理
						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex2d(width * 320 / 1600, height * (130 + j * 100) / 1200);
						glTexCoord2f(1.0f, 0.0f); glVertex2d(width * 400 / 1600, height * (130 + j * 100) / 1200);
						glTexCoord2f(1.0f, 1.0f); glVertex2d(width * 400 / 1600, height * (50 + j * 100) / 1200);
						glTexCoord2f(0.0f, 1.0f); glVertex2d(width * 320 / 1600, height * (50 + j * 100) / 1200);
						glEnd();
						char status[100];
						if (((TheOrbOfTheHero*)player->getUseItems()[i])->getDamageOfMonster(j) < 0)
							sprintf_s(status, "%s: Cannot be hit by you", ((TheOrbOfTheHero*)player->getUseItems()[i])->getNameOfMonster(j));
						else
							sprintf_s(status, "%s: Expected damage %d", ((TheOrbOfTheHero*)player->getUseItems()[i])->getNameOfMonster(j), ((TheOrbOfTheHero*)player->getUseItems()[i])->getDamageOfMonster(j));
						glPrint(width * 420 / 1600, height * (50 + j * 100) / 1200, status, (float)2 / 1600 * width);
						sprintf_s(status, "Life %d Offence %d Defense %d Money %d", ((TheOrbOfTheHero*)player->getUseItems()[i])->getHealthOfMonster(j), ((TheOrbOfTheHero*)player->getUseItems()[i])->getAttackOfMonster(j), ((TheOrbOfTheHero*)player->getUseItems()[i])->getDefenceOfMonster(j), ((TheOrbOfTheHero*)player->getUseItems()[i])->getMoneyOfMonster(j));
						glPrint(width * 420 / 1600, height * (90 + j * 100) / 1200, status, (float)2 / 1600 * width);
					}
					glDisable(GL_BLEND);
					break;
				}
				case 1: // The orb of wisdom
				{
					char* message = ((TheOrbOfWisdom*)player->getUseItems()[i])->getMessage();
					if (message != NULL)
					{
						dialogDraw(message, false);
						messageDraw("Press A to previous, Press D to next sentence");
					}
					else
					{
						dialogDraw("There is no setence.", false);
						messageDraw("There is no setence.");
					}
					break;
				}
				case 2: // The orb of flying
				{
					glBindTexture(GL_TEXTURE_2D, dialogTexture); // 选择纹理
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex2d(width * 270 / 1600, height * 760 / 1200);
					glTexCoord2f(1.0f, 0.0f); glVertex2d(width * 680 / 1600, height * 760 / 1200);
					glTexCoord2f(1.0f, 1.0f); glVertex2d(width * 680 / 1600, height * 560 / 1200);
					glTexCoord2f(0.0f, 1.0f); glVertex2d(width * 270 / 1600, height * 560 / 1200);
					glEnd();
					glEnable(GL_BLEND);
					char floor[10];
					for (int j = 0; j < player->getMaxFloor(); j++)
					{
						sprintf_s(floor, "%d", j + 1);
						glPrint(width* (270 + (j % 10) * 40) / 1600, height* (560 + (j / 10) * 40) / 1200, floor, (float)1.7 / 1600 * width);
					}
					glDisable(GL_BLEND);
					break;
				}
				default:
					break;
				}
			}
		}
	}

	// 楼层移动动画(必须置于最顶层)
	if (isUsingStairs)
	{
		if (map[3][3])
		{
			direction = new Vector2(1, 0);
			position = new Vector2(0, 0);
			isUsingStairs = !isUsingStairs;
		}
		else
		{
			map[(int)floor(position->x + 0.5f)][(int)floor(position->y + 0.5f)] = true;
			position->x += direction->x;
			position->y += direction->y;
			if ((int)floor(position->x + 0.5f + direction->x) > 6 || (int)floor(position->x + 0.5f + direction->x) < 0 || (int)floor(position->y + direction->y + 0.5f) > 6 || map[(int)floor(position->x + direction->x + 0.5f)][(int)floor(position->y + direction->y + 0.5f)])
			{
				if (direction->x == 0 && direction->y == 1)
					direction = new Vector2(-1, 0);
				else if (direction->x == 1 && direction->y == 0)
					direction = new Vector2(0, 1);
				else if (direction->x == 0 && direction->y == -1)
					direction = new Vector2(1, 0);
				else if (direction->x == -1 && direction->y == 0)
					direction = new Vector2(0, -1);
			}
		}
	}
	if (isFinishUsingStairs)
	{
		if (!map[3][3])
		{
			direction = new Vector2(1, 0);
			position = new Vector2(0, 0);
			isFinishUsingStairs = !isFinishUsingStairs;
		}
		else
		{
			map[(int)floor(position->x + 0.5f)][(int)floor(position->y + 0.5f)] = false;
			position->x += direction->x;
			position->y += direction->y;
			if ((int)floor(position->x + direction->x + 0.5f) > 6 || (int)floor(position->x + direction->x + 0.5f) < 0 || (int)floor(position->y + direction->y + 0.5f) > 6 || !map[(int)floor(position->x + direction->x + 0.5f)][(int)floor(position->y + direction->y + 0.5f)])
			{
				if (direction->x == 0 && direction->y == 1)
					direction = new Vector2(-1, 0);
				else if (direction->x == 1 && direction->y == 0)
					direction = new Vector2(0, 1);
				else if (direction->x == 0 && direction->y == -1)
					direction = new Vector2(1, 0);
				else if (direction->x == -1 && direction->y == 0)
					direction = new Vector2(0, -1);
			}
		}
	}
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (map[i][j])
			{
				glEnable(GL_TEXTURE_2D); // 开启2D纹理
				glBindTexture(GL_TEXTURE_2D, usingStairs);		// 选择纹理
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (300 + i * (1020 / 7)) / 1600, height * ((j + 1) * (1144 / 7)) / 1200);
				glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (300 + (i + 1) * (1020 / 7)) / 1600, height * ((j + 1) * (1144 / 7)) / 1200);
				glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (300 + (i + 1) * (1020 / 7)) / 1600, height * (j * (1144 / 7)) / 1200);
				glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (300 + i * (1020 / 7)) / 1600, height * (j * (1144 / 7)) / 1200);
				glEnd();
			}
		}
	}
}

void UIManager::loadMonster(Monster* monster)
{
	this->monster = monster;
}

UIManager::UIManager(int width, int height)
{
	this->width = width;
	this->height = height;
	this->monster = NULL;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			map[i][j] = false;
		}
	}
	this->position = new Vector2(0, 0);
	this->direction = new Vector2(1, 0);
}

void UIManager::setWindow(int width, int height)
{
	this->width = width;
	this->height = height;
}

void UIManager::dialogDraw(char* sentence, bool isChoose)
{
	this->dialogDrawing = true;
	sprintf_s(this->sentence, sentence);
	this->isChoose = isChoose;
}

void UIManager::messageDraw(char* message)
{
	this->messaging = true;
	sprintf_s(this->message, message);
}
