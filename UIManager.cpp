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
	float cx;							// �洢����x,y�������ʱ����
	float cy;

	base = glGenLists(256);				// �洢256���ַ�
	glBindTexture(GL_TEXTURE_2D, font[0]);			// ѡ�����������
	for (int i = 0; i < 256; i++)					// ��256���ַ�������������
	{
		cx = float(i % 16) / 16.0f;					// 16���ַ�һ�У���������ѡ������ģ�������Կ�һ��Data/Font.bmp��
		cy = float(i / 16) / 16.0f;

		glNewList(base + i, GL_COMPILE);
		glBegin(GL_QUADS);								// ��һ�������ν������ǵ�������
		glTexCoord2f(cx, 1 - cy - 0.0625f);				// �������� (����)
		glVertex2i(0, 16);								// �����εĵ����� (����)
		glTexCoord2f(cx + 0.0625f, 1 - cy - 0.0625f);	// �������� (����)
		glVertex2i(16, 16);								// �����εĵ����� (����)
		glTexCoord2f(cx + 0.0625f, 1 - cy);				// �������� (����)
		glVertex2i(16, 0);								// �����εĵ����� (����)
		glTexCoord2f(cx, 1 - cy);						// �������� (����)
		glVertex2i(0, 0);								// �����εĵ����� (����)
		glEnd();
		glTranslated(10, 0, 0);							// �ƶ��ַ�
		glEndList();
	}
}

void UIManager::glPrint(int x, int y, char* string, float scale)
{
	glBindTexture(GL_TEXTURE_2D, font[0]);			// ѡ����������
	glTranslated(x, y, 0);								// �ƶ��ı�
	glScalef(scale, scale, 1);
	glListBase(base - 32);								// ������ʾ�б�
	glCallLists(strlen(string), GL_BYTE, string);		// ���ı�ͶӰ����Ļ��
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
		glBindTexture(GL_TEXTURE_2D, left[0]); // ʹ��������������ӽ������ɸ���ɫ��ͨ����Ȩƽ���㷨�õ���Ҫ���Ƶ�������ɫ
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
		glBindTexture(GL_TEXTURE_2D, right[0]); // ʹ��������������ӽ������ɸ���ɫ��ͨ����Ȩƽ���㷨�õ���Ҫ���Ƶ�������ɫ
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
		glBindTexture(GL_TEXTURE_2D, bottom[0]); // ʹ��������������ӽ������ɸ���ɫ��ͨ����Ȩƽ���㷨�õ���Ҫ���Ƶ�������ɫ
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
		glBindTexture(GL_TEXTURE_2D, font[0]); // ʹ��������������ӽ������ɸ���ɫ��ͨ����Ȩƽ���㷨�õ���Ҫ���Ƶ�������ɫ
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
			glBindTexture(GL_TEXTURE_2D, key[i]); // ʹ��������������ӽ������ɸ���ɫ��ͨ����Ȩƽ���㷨�õ���Ҫ���Ƶ�������ɫ
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
	// ����ߵ�UI
	glEnable(GL_TEXTURE_2D); // ����2D����
	glBindTexture(GL_TEXTURE_2D, left[0]);		// ѡ������
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(0, height * 20 / 21);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width * 3 / 16, height * 20 / 21);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width * 3 / 16, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
	glEnd();
	// ���ұߵ�UI��
	glEnable(GL_TEXTURE_2D); // ����2D����
	glBindTexture(GL_TEXTURE_2D, right[0]);		// ѡ������
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(width * 13 / 16, height * 20 / 21);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width, height * 20 / 21);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(width * 13 / 16, 0);
	glEnd();
	// �����µ���Ϣ��
	glEnable(GL_TEXTURE_2D); // ����2D����
	glBindTexture(GL_TEXTURE_2D, bottom[0]);		// ѡ������
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(0, height);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width, height);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width, height * 20 / 21);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(0, height * 20 / 21);
	glEnd();

	glEnable(GL_BLEND);
	// ��ʾmessage
	if (messaging)
		glPrint(width * 5 / 1600, height * ((1200 * 20 / 21) + 5) / 1200, this->message, (float)3 / 1600 * width);

	char string[100];
	// ��ʾ����
	sprintf_s(string, "Tower %d", player->getFloor());
	glPrint((int)(((float)38/1600)*width), (int)(((float)148/1200)*height), string, ((float)240 / (float)(strlen(string) * 11.5f))/1600 * width);
	// ��ʾ����
	sprintf_s(string, "%d", player->getHealth());
	glPrint((int)((260 - strlen(string) * 32) / (float)1600 * width), (int)(((float)230 / 1200) * height), string, (float)3 / 1600 * width);
	sprintf_s(string, "%d", player->getAttack());
	glPrint((int)((260 - strlen(string) * 32) / (float)1600 * width), (int)(((float)298 / 1200) * height), string, (float)3 / 1600 * width);
	sprintf_s(string, "%d", player->getDefence());
	glPrint((int)((260 - strlen(string) * 32) / (float)1600 * width), (int)(((float)366 / 1200) * height), string, (float)3 / 1600 * width);
	sprintf_s(string, "%d", player->getMoney());
	glPrint((int)((260 - strlen(string) * 32) / (float)1600 * width), (int)(((float)434 / 1200) * height), string, (float)3 / 1600 * width);

	GLuint texture;
	// ����������
	for (unsigned short i = 0; i < 15; i++)
	{
		if (player->getUseItems()[i] != NULL)
		{
			if ((player->getUseItems()[i])->isEnable())
			{
				texture = (player->getUseItems()[i])->getTexture();
				glEnable(GL_TEXTURE_2D); // ����2D����
				glBindTexture(GL_TEXTURE_2D, texture);		// ѡ������
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (76 + 75 * (i % 3) - 36) / 1600, height * (596 + 88 * (i / 3) + 36) / 1200);
				glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (76 + 75 * (i % 3) + 36) / 1600, height * (596 + 88 * (i / 3) + 36) / 1200);
				glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (76 + 75 * (i % 3) + 36) / 1600, height * (596 + 88 * (i / 3) - 36) / 1200);
				glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (76 + 75 * (i % 3) - 36) / 1600, height * (596 + 88 * (i / 3) - 36) / 1200);
				glEnd();
			}
		}
	}
	// �����Ͷ�
	if (player->getSwordTexture() != 0)
	{
		sprintf_s(string, "%s", player->getSwordName());
		glPrint(width * 1328 / 1600, height * 192 / 1200, string, width * 2.5f / 1600);

		texture = player->getSwordTexture();
		glEnable(GL_TEXTURE_2D); // ����2D����
		glBindTexture(GL_TEXTURE_2D, texture);		// ѡ������
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
		glPrint(width * 1328 / 1600, height * 332 / 1200, string, width * 2.5f / 1600);

		texture = player->getShieldTexture();
		glEnable(GL_TEXTURE_2D); // ����2D����
		glBindTexture(GL_TEXTURE_2D, texture);		// ѡ������
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (1526 - 36) / 1600, height * 363 / 1200);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (1526 + 36) / 1600, height * 363 / 1200);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (1526 + 36) / 1600, height * 291 / 1200);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (1526 - 36) / 1600, height * 291 / 1200);
		glEnd();
	}
	// ��Կ��
	int index = 0;
	for (int i = 0; i < player->getRedKeyNumber(); i++)
	{
		// ����Կ��
		texture = key[0];
		if (index < 24)
		{
			glEnable(GL_TEXTURE_2D); // ����2D����
			glBindTexture(GL_TEXTURE_2D, texture);		// ѡ������
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
		// ����Կ��
		texture = key[1];

		if (index < 24)
		{
			glEnable(GL_TEXTURE_2D); // ����2D����
			glBindTexture(GL_TEXTURE_2D, texture);		// ѡ������
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
		// ����Կ��
		texture = key[2];
		if (index < 24)
		{
			glEnable(GL_TEXTURE_2D); // ����2D����
			glBindTexture(GL_TEXTURE_2D, texture);		// ѡ������
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(width * (1327 + (index % 6) * (double)234 / 6) / 1600, height * (409 + ((double)(index / 6) + 1) * (double)185 / 4) / 1200);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(width * (1327 + ((double)(index % 6) + 1) * (double)234 / 6) / 1600, height * (409 + ((double)(index / 6) + 1) * (double)185 / 4) / 1200);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(width * (1327 + ((double)(index % 6) + 1) * (double)234 / 6) / 1600, height * (409 + (index / 6) * (double)185 / 4) / 1200);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(width * (1327 + (index%6) * (double)234/6) / 1600, height * (409 + (index/6) * (double)185/4) / 1200);
			glEnd();
		}
		index++;
	}

	// ����������
	if (monster != NULL)
	{
		// ����������
		texture = monster->getTexture();
		glEnable(GL_TEXTURE_2D); // ����2D����
		glBindTexture(GL_TEXTURE_2D, texture);		// ѡ������
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
}

void UIManager::setWindow(int width, int height)
{
	this->width = width;
	this->height = height;
}

void UIManager::dialogDraw(char* setence, bool isChoose)
{
	this->dialogDrawing = true;
	sprintf_s(this->setence, setence);
	this->isChoose = true;
}

void UIManager::messageDraw(char* message)
{
	this->messaging = true;
	sprintf_s(this->message, message);
}
