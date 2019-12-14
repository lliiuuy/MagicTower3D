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
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, font[0]);			// ѡ����������
	glTranslated(x, y, 0);								// �ƶ��ı�
	glScalef(scale, scale, 1);
	glListBase(base - 32);								// ������ʾ�б�
	glCallLists(strlen(string), GL_BYTE, string);		// ���ı�ͶӰ����Ļ��
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
	glMatrixMode(GL_PROJECTION);						// ѡ��͸�Ӿ���
	glLoadIdentity();									// ����͸�Ӿ���

	glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);   // ����ƽ��ͶӰ

	glMatrixMode(GL_MODELVIEW);							// ѡ��ģ�;���
	glLoadIdentity();									// ��������ģ�;���

	glEnable(GL_TEXTURE_2D); // ����2D����
	glBindTexture(GL_TEXTURE_2D, left[0]);		// ѡ������
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(0, height * 20 / 21);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width * 3 / 16, height * 20 / 21);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width * 3 / 16, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
	glEnd();

	glEnable(GL_TEXTURE_2D); // ����2D����
	glBindTexture(GL_TEXTURE_2D, right[0]);		// ѡ������
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(width * 13 / 16, height * 20 / 21);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width, height * 20 / 21);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(width * 13 / 16, 0);
	glEnd();

	glEnable(GL_TEXTURE_2D); // ����2D����
	glBindTexture(GL_TEXTURE_2D, bottom[0]);		// ѡ������
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(0, height);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(width, height);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(width, height * 20 / 21);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(0, height * 20 / 21);
	glEnd();

	char string[100];
	// ��ʾ����
	sprintf_s(string, "Tower %d", 15);
	glPrint((int)(((float)40/1600)*width), (int)(((float)150/1200)*height), string, ((float)240 / (float)(strlen(string) * 11))/1600 * width);
	// ��ʾ����
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
	// ����������
	for (unsigned short i = 0; i < player->getUseItem()->size(); i++)
	{
		int index = (*(player->getUseItem()))[i]->getIndex();
		texture = (*(player->getUseItem()))[i]->getTexture();

	}
	// �����Ͷ�
	if (player->getSword() != NULL)
	{
		sprintf_s(string, "%s", player->getSword()->getUIName());
		texture = player->getSword()->getTexture();
	}
	// ��Կ��
	int index = 0;
	for (int i = 0; i < player->getRedKeyNumber(); i++)
	{
		// ����Կ��
		index++;
	}
	for (int i = 0; i < player->getBlueKeyNumber(); i++)
	{
		// ����Կ��
		index++;
	}
	for (int i = 0; i < player->getYellowKeyNumber(); i++)
	{
		// ����Կ��
		index++;
	}

	// ����������
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
	glMatrixMode(GL_PROJECTION);						// ѡ��͸�Ӿ���
	glLoadIdentity();									// ����͸�Ӿ���

	gluPerspective(45.0f, 1, 0.1f, 1000.0f); //	���û�͸��ͶӰ

	glMatrixMode(GL_MODELVIEW);							// ѡ��ģ�;���
	glLoadIdentity();									// ��������ģ�;���
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
